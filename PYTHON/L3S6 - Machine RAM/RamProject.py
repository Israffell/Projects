class RamProject:
        
    '''Initialisation du programme RAM avec les Consignes à suivre'''
    def __init__ (self, dataTab=[], txt=[]):
        self.data = dataTab
        self.step = 0
        self.register = {}        

        for i, e in enumerate(txt):
            self.register['I{}'.format(i)] = e


    '''Met à jour si c'est un adressage directe/indirecte'''
    def address (self, val):
        if val[0] in ('I', 'R', 'O'):
            if val[1] == '#':
                return '{}{}'.format(val[0], self.value(val.split('#')[1]))
            else:
                return val


    '''Met à jour le registre de la machine RAM via des adressage directe/indirecte'''
    def value (self, val):
        if val[0] in ('I', 'R', 'O'):
            if val[1] == '#':
                return self.register['{}{}'.format(val[0], self.value(val.split('#')[1]))]
            else:
                return self.register[val]
        else:
            return int(val)



    '''Permet l'affichage graphique'''
    def display(self):
        displayTab = []
        step = 0
        dataTab = self.getProgram()
        last = len(dataTab)

        for instr in dataTab:
            operand, *args = instr.split('(')
            args = args[0].split(')')[0].split(',')
            
            if operand in ['ADD', 'SUB', 'MUL', 'DIV']:
                displayTab.append((step, step + 1))
            elif operand in ['JUMP', 'JE', 'JL']:
                if len(args) >= 3:
                    value = self.value(args[2])
                    countStep = step + value + (1 if value > 0 else (-1 if value < 0 else 0))
                    countStep = max(0, min(countStep, last))
                    displayTab.append((step, step + 1))
                    displayTab.append((step, countStep))
                else:
                    displayTab.append((step, step + 1))

            step += 1

        return (last, displayTab)



    '''Retranscription des conditions choisis précédement en application arithmétique '''
    def newStep (self):
        print(self.getData())

        operand, args = self.getData().split('(')
        args = args.split(')')[0].split(',')
        countStep = 1

        if operand == 'ADD':
            self.register[self.address(args[2])] = self.value(args[0]) + self.value(args[1])
        elif operand == 'SUB':
            self.register[self.address(args[2])] = self.value(args[0]) - self.value(args[1])
        elif operand == 'MUL':
            self.register[self.address(args[2])] = self.value(args[0]) * self.value(args[1])
        elif operand == 'DIV':
            self.register[self.address(args[2])] = self.value(args[0]) // self.value(args[1])
        elif operand == 'JUMP':
            size = self.value(args[0])
            countStep = size - 1 if size < 0 else size + 1
        elif operand == 'JE':
            if self.value(args[0]) == self.value(args[1]):
                size = self.value(args[2])
                countStep = size - 1 if size < 0 else size + 1
        elif operand == 'JL':
            if self.value(args[0]) < self.value(args[1]):
                size = self.value(args[2])
                countStep = size - 1 if size < 0 else size + 1

        self.setStep(self.getStep() + countStep)



    '''Détection des Steps fonctionel et ceux inutiles après avoir vérifié si ils étaient utilisé '''
    def deadDetection (self):
        def validState(modification:list, actualState:int):
            validTab = []
            for startingState, finalState in modification:
                if startingState == actualState:
                    validTab.append(finalState)
            return validTab

        validTab = set()
        lastValues = [0]
        size, modification = self.display()

        while lastValues:
            newValue = []
            for state in lastValues:
                temp = validState(modification, state)
                for i in temp:
                    if i not in validTab:
                        newValue.append(i)
            validTab.update(newValue)
            lastValues = newValue
        wrongValues = set()
        
        for f in range(size, 0, -1):
            if f not in validTab:
                wrongValues.add(f)
        return wrongValues



    '''Supression des conditions inutilisées '''
    def codeDeletion (self, countStep:set):
        wrongStates = []
        modification = []

        for step, instr in enumerate(self.getProgram()):

            if ((instruction := instr.split('(')[0]) in {'JUMP', 'JE', 'JL'}) and (step not in countStep):

                if instruction == 'JUMP':
                    size = int(instr.split('(')[1] .split(')')[0])
                    body = 'JUMP('
                else:
                    size = int(instr.split('(')[1] .split(')')[0] .split(',')[2])
                    body = str(instr.split(',')[0] + ',' + instr.split(',')[1] + ',')

                tempo = 0
                sign = 1 if size >= 0 else -1
                
                for i in range(sign, size + sign, sign):
                    if (step + i) in countStep:
                        tempo += 1

                if tempo:
                    new_size = (size - (sign * tempo))

                    if new_size:
                        new_instr = body + str(new_size) + ')'
                    else:
                        new_instr = 0
                        
                modification.append((step, new_instr))

        for difference in modification:
            if difference[1]:
                self.setData(*difference)
            else:
                wrongStates.append(difference[0])

        countStep = sorted(list(countStep), reverse=True)
        for step in countStep:
            self.delDataStep(step)

        if wrongStates:
            self.codeDeletion(set(wrongStates))



    '''Le 'corps' du fichier RamProject.py permettant l'execution du projet '''
    def executeProject(self):
        print('\nStarting the Project:\n')
        print(f'Graph (Number of last, modification):\n{str(display := self.display())}\n')

        if (countStep := self.deadDetection()):

            notReachable = []
            for i in countStep:
                if i == display[0]:
                    raise SyntaxError('It is impossible')
                else:
                    notReachable.append(self.getData(i))
            
            delete = str(input(f'The following terms are never valid: {notReachable}\nStep(s):  {countStep}\nRemove the unused terms?\n Type "y" for YES | Otherwise press "enter" to PASS\n  >'))

            if delete == 'y':
                file = open('textEntrance.txt', 'w')
                self.codeDeletion(countStep)                
                entry = ''
                
                for elem in self.getAr('I'):
                    entry += str(elem.split(':')[1] + ',')
                    
                entry = entry[:-1]
                entry += '\n'
                
                for instr in self.getProgram():
                    entry += instr + '\n'
                    
                entry = entry[:-1]
                
                file.write(entry)
                file.close()

                self.executeProject()

        else:
            print('There is no deadcode\n')

            while self.getStep() < len(self.data):
                self.newStep()
                self.printSteps()

            print('The Output is: ' + str(self.getAr('O')))
            print()
            print()



    '''Affichage graphique dans le terminal des détails de chaque STEPS et leur position '''
    def printSteps (self):
        print('The STEP number is at the line', self.getStep()+1,)   # + 1 cause the first line of the .txt is taken by the values 
        print('I =', ' || '.join(self.getAr('I')))
        print('R =', ' || '.join(self.getAr('R')))
        print('O =', ' || '.join(self.getAr('O')))
        print()


    '''Envoie les valeurs du programme '''
    def getProgram (self):
        return self.data


    '''Envoie la position de la consigne '''
    def getStep (self):
        return self.step


    '''Envoie la condition selectionné au programme '''
    def getData (self, step=None):
        if step is None:
            return self.data[self.step]
        return self.data[step]


    '''Permet d'accéder au "REGISTRE" autrement dit la mémoire temporaire '''
    def getR (self):
        return self.register    
    
    
    '''Permet de renvoyer les valeurs selectionner du REGISTRE à la bande de sortie '''
    def getAr (self, iro):
        result = []
        for k, v in self.getR().items():
            if k[0] == iro:
                result.append(('{} : {}').format(k, v))
        return result


    '''Actualisation du Step dans laquel nous travaillons '''
    def setStep (self, newStep):
        self.step = newStep
        
        
    '''Actualisation de la consigne de travail '''
    def setData (self, index: int, newData: str):
        self.data[index] = newData


    '''Supression d'une consigne '''
    def delDataStep (self, step: int):
        del self.data[step]