  // Initialisation des variables globales
  
  String[] lines = null;
  int Px=0;
  int Py=0;
  int taille_case = 30;
  int milieu = (taille_case /2);
  int skinpacman = 0; 
  int UI=0;
  int play=0;
  int compteur=0;   
  int noreplay=0;
  
  int M1x=0, M1y=0;
  int M2x=0, M2y=0;
  int M3x=0, M3y=0;
  int M4x=0, M4y=0;
  int DM1=1, DM2=2;
  int DM3=1, DM4=2;
  
  boolean start = false;
  boolean win;
  boolean son = true;
  
  
  //Importation de Minim pour l'audio et gifAnimation pour les .gifs
  
  import ddf.minim.*;
  Minim minim;
  AudioPlayer Song;
  AudioPlayer victorytheme;
  AudioPlayer loosetheme;
  AudioPlayer starttheme;
 
  import gifAnimation.*;
  Gif XPChargement;
  Gif PacChargement;
  Gif Home;
  
  
  //Initialisation du programme
  
  void setup(){
    frameRate(60);
    size(1500,800);
    surface.setResizable(true);
    lines = loadStrings("data/UI.txt");
    
    if(play == 0){
    Chargement();
    Menu();
    Musique();
    
    }
    
    for (int i = 0 ; i < 22; i++) { //Récupération des coordonnées des monstres et des joueurs
      
      for (int j = 0 ; j < 19; j++){
        if(lines[i].charAt(j) == '@'){
          Px=i;
          Py=j;
         }
        if(lines[i].charAt(j) == '$'){
          M1x=i;
          M1y=j;
          lines[M1x]= lines[M1x].substring(0,M1y) + 'c' + lines[M1x].substring(M1y+1);
         }
        if(lines[i].charAt(j) == '%'){
          M2x=i;
          M2y=j;
          lines[M2x]= lines[M2x].substring(0,M2y) + 'c' + lines[M2x].substring(M2y+1);
         }
        if(lines[i].charAt(j) == '*'){
          M3x=i;
          M3y=j;
          lines[M3x]= lines[M3x].substring(0,M3y) + 'c' + lines[M3x].substring(M3y+1);
         }
        if(lines[i].charAt(j) == '?'){
          M4x=i;
          M4y=j;
          lines[M4x]= lines[M4x].substring(0,M4y) + 'c' + lines[M4x].substring(M4y+1);
         }
       }
    }
  }
  
  
  //Fonction graphique princpale qui s'actualise en permanence
  
  void draw(){
    PImage SonOO;
    background(#000000);
    win();
    
    if (noreplay == 0){;    
    WinTheme();
   }
    
    if(play == 1){
     if(win){
      noreplay=1;
     }}
    
    int m=millis();
   
   if(play == 0){
    if(m<10000){
      image(XPChargement, 0, 0,1450,900);     
      image(PacChargement,525,600,400,200);
    }
    if(m>10000){
      image(Home,0,0,1450,900);
      fill(0,204,203);
      strokeWeight(4);
      stroke(102,0,255);
      rect(380,41,210,85,20);      
      fill(#000000);
      text("Play", 408 , 110 );
      textSize(75);
    }
   }
    
    if(play == 1){
    if(compteur == 9 && start){
      lose();
      deplacementJoueur(UI);
      deplacementMonstre(1);
      deplacementMonstre(2);
      deplacementMonstre(3);
      deplacementMonstre(4);
      lose();
    }
    compteur ++;
    
    Afficher();
        
    if(!start){
      fill(0,204,203);
      strokeWeight(4);
      stroke(102,0,255);
      rect(185,260,200,115,20);      
      fill(#000000);
      text("Play", 186, 350); 
      textSize(100);
    }
    if(win){
      fill(0,204,203);
      strokeWeight(4);
      stroke(102,0,255);
      rect(185,260,200,115,20);
      fill(#000000);
      text("WIN", 195, 355); 
      textSize(100);
      start=false;
    }
    
    if(son == false){
      SonOO = loadImage("data/son_on.png");
      SonOO.resize(30, 30);
      image(SonOO,540,0);
    }
    
    if(son == true){
      SonOO = loadImage("data/son_off.png");
      SonOO.resize(30, 30);
      image(SonOO,540,0);
    }
    }
  }
  
  
  //Fonction pour afficher les murs, le pac-man, les monstres, les balles, les portails grâce au fichier UI.txt
  
  void Afficher(){
    for (int i = 0 ; i < lines.length; i++) {
      
    for (int j = 0 ; j < 19; j++){
              switch (lines[i].charAt(j)) {
        case '#':
          Mur mur = new Mur(j * taille_case, i * taille_case);
          mur.display();
          break;
        case '@':
          Joueur joueur = new Joueur((j * taille_case)+ milieu,  (i * taille_case)+ milieu);
          joueur.display();
          break;
        case ' ':
          break;
        case 'c':
          Coins coins = new Coins((j * taille_case)+ milieu,  (i * taille_case)+ milieu);
          coins.display();
          break;
        case '>':
          Portail portail1 = new Portail((j * taille_case),  (i * taille_case), 0);
          portail1.display();
          break;
        case '<':
          Portail portail2 = new Portail((j * taille_case),  (i * taille_case), 1);
          portail2.display();
          break;
        }
      }
    }
      Monstre monstreR = new Monstre((M1y * taille_case),  (M1x * taille_case), 0);
      monstreR.display();
      
      Monstre monstreB = new Monstre((M2y * taille_case),  (M2x * taille_case), 1);
      monstreB.display();
      
      Monstre monstreJ = new Monstre((M3y * taille_case),  (M3x * taille_case), 2);
      monstreJ.display();
      
      Monstre monstreV = new Monstre((M4y * taille_case),  (M4x * taille_case), 3);
      monstreV.display();
  }
  
  
  //Fonction son lorsqu'on gagne, perd, bouton play
  
  void WinTheme(){
    if(play == 1){
     if(win){
      Song.pause();      
      son = false;
      Winsong();
     }}}
     
     
   void DeathTheme(){
     Song.pause();
     Deathsong();
     son = false;
   }
   
   
   
   void BeginTheme(){     
     Song.pause();
     Beginsong();
     son = false;
   }
  
  
  //Fonction déplacement joeur
  
  
  void deplacementJoueur(int direction){
    compteur=0;
    switch(direction){
      
      case 1:
      UI=1;
        if(lines[Px].charAt(Py-1) !='#'){
          if(lines[Px].charAt(Py-1) =='>'){
           lines[Px]= '>' + ' ' +  lines[Px].substring(2, Py+16) + '@' + '<';
           lines[Px]= '>' + lines[Px].substring(1);
           Py=Py+16;
           skinpacman = 1;
          }
          
        else {
        lines[Px]= lines[Px].substring(0,Py-1) + '@' + ' ' + lines[Px].substring(Py+1);
        Py=Py-1;
        skinpacman = 1;
        }
        }
        break;
        
      case 2:
      UI=2;
        if(lines[Px].charAt(Py+1) !='#'){
          if(lines[Px].charAt(Py+1) =='<'){
          lines[Px]= lines[Px].substring(0,1) + '@' +  lines[Px].substring(2, Py) + ' ' + '<';
          Py=Py-16;
          skinpacman = 2;
          }
          
        else  {
        lines[Px]= lines[Px].substring(0,Py) + ' ' + '@' + lines[Px].substring(Py+2);
        Py=Py+1;
        skinpacman = 2;
        }
        }
        break;
        
      case 3:
      UI=3;
       if(lines[Px-1].charAt(Py) !='#'){
        lines[Px-1]= lines[Px-1].substring(0,Py) + '@' + lines[Px-1].substring(Py+1);
        lines[Px]= lines[Px].substring(0,Py) + ' ' + lines[Px].substring(Py+1);
        Px=Px-1;
        skinpacman = 3;
        }
        break;
        
      case 4:
      UI=4;
       if(lines[Px+1].charAt(Py) !='#'){
        lines[Px+1]= lines[Px+1].substring(0,Py) + '@' + lines[Px+1].substring(Py+1);
        lines[Px]= lines[Px].substring(0,Py) + ' ' + lines[Px].substring(Py+1);
        Px=Px+1;
        skinpacman = 4;
        }
        break;
    }
  }
  
  
  //Fonction déplacement monstre
  
  void deplacementMonstre(int Monstres ){
    int x=0, y=0, Adirection=0, direction= int(random(1,5));
    char skinM;
    switch(Monstres){
      case 1:
      x=M1x; y=M1y; Adirection=DM1; skinM = '$';
        break;
        
      case 2:
      x=M2x; y=M2y; Adirection=DM2; skinM = '%';
        break;
        
      case 3:
      x=M3x; y=M3y; Adirection=DM3; skinM = '*';
        break;
        
      case 4:
      x=M4x; y=M4y; Adirection=DM4; skinM = '?';
        break;
    }
    
     if(Adirection == 1){
       if(direction == 1){
        if(lines[x].charAt(y-1) !='#'){
          if(lines[x].charAt(y-1) =='>'){
           y=y+16;
           Adirection = 1;
          }
          
        else {
        y=y-1;
        Adirection = 1;
        }
        }
      }
      
      if(direction == 3){
       if(lines[x-1].charAt(y) !='#'){
        x=x-1;
        Adirection = 3;
        }
     }
        
     if(direction == 4){
       if(lines[x+1].charAt(y) !='#'){
        x=x+1;
        Adirection = 4;
        }
     }
     }
     
     if(Adirection == 2){
       if(direction == 2){
        if(lines[x].charAt(y+1) !='#'){
          if(lines[x].charAt(y+1) =='<'){
          y=y-16;
          Adirection = 2;
          }
          
        else  {
        y=y+1;
        Adirection = 2;
        }
        }
        }
        
      
     if(direction == 3){
       if(lines[x-1].charAt(y) !='#'){
        x=x-1;
        Adirection = 3;
        }
     }
        
     if(direction == 4){
       if(lines[x+1].charAt(y) !='#'){
        x=x+1;
        Adirection = 4;
        }
     }
     }
     
     if(Adirection == 3){
       if(direction == 1){
        if(lines[x].charAt(y-1) !='#'){
          if(lines[x].charAt(y-1) =='>'){
           y=y+16;
           Adirection = 1;
          }
          
        else {
        y=y-1;
        Adirection = 1;
        }
        }
      }
    
      if(direction == 2){
        if(lines[x].charAt(y+1) !='#'){
          if(lines[x].charAt(y+1) =='<'){
          y=y-16;
          Adirection = 2;
          }
          
        else  {
        y=y+1;
        Adirection = 2;
        }
        }
        }
        
         if(direction == 3){
       if(lines[x-1].charAt(y) !='#'){
        x=x-1;
        Adirection = 3;
        }
     }
     }
     
     if(Adirection == 4){
       if(direction == 1){
        if(lines[x].charAt(y-1) !='#'){
          if(lines[x].charAt(y-1) =='>'){
           y=y+16;
           Adirection = 1;
          }
          
        else {
        y=y-1;
        Adirection = 1;
        }
        }
      }
    
      if(direction == 2){
        if(lines[x].charAt(y+1) !='#'){
          if(lines[x].charAt(y+1) =='<'){
          y=y-16;
          Adirection = 2;
          }
          
        else  {
        y=y+1;
        Adirection = 2;
        }
        }
        }
        
        if(direction == 4){
       if(lines[x+1].charAt(y) !='#'){
        x=x+1;
        Adirection = 4;
        }
     }
     }
    
    switch(Monstres){
      case 1:
      M1x=x; M1y=y; DM1=Adirection;
        break;
        
      case 2:
      M2x=x; M2y=y; DM2=Adirection;
        break;
      case 3:
      M3x=x; M3y=y; DM3=Adirection;
        break;
        
      case 4:
      M4x=x; M4y=y; DM4=Adirection;
        break;
    }
   }
  
   
   //Fonction défaite
   
  void lose(){
    if((Px == M1x && Py == M1y ) || (Px == M2x && Py == M2y) )  {
        DeathTheme();
        start = false;
        setup();
    }
    else if((Px == M3x && Py == M3y ) || (Px == M4x && Py == M4y) )  {
        DeathTheme();
        start = false;
        setup();
         }
  }
   
   
   //Fonction victoire
   
   void win(){
     win=false;
      for (int i = 0 ; i < 22; i++) {
      
        for (int j = 0 ; j < 19; j++){
          if(lines[i].charAt(j) == 'c'){
           return;
         }
       }
      }
      win=true;
    }
   
   
   
  void keyPressed() {
    if (key == CODED && start) {
      if (keyCode == LEFT) {
        deplacementJoueur(1);
      }
      
      else if (keyCode == RIGHT) {
        deplacementJoueur(2);
      }
      
      else if (keyCode == UP) {
        deplacementJoueur(3);
      }
      
      else if (keyCode == DOWN) {
        deplacementJoueur(4);
      }
      else if (keyCode == ESC) {
        exit();
      }
    }
  }
  
  
  //Fonction clique souris
  
  void mouseClicked() {
    if(((mouseX >=380) && (mouseX <=590))&& ((mouseY >=41)&& (mouseY <=126)) && play == 0){
    play = 1;
    surface.setSize(570,660);        
    start = false;
    setup();
    compteur = 0;
    BeginTheme();
    son = false;
    }
    
   
    
    else {
      if(((mouseX >=185)&&(mouseX <=385)) && ((mouseY >=260)&&(mouseY <=375))){
      start= true;
      Song.play();
      son = true;      
     }
   }
     
    if(((mouseX >=540)&&(mouseX <=570))&& ((mouseY >=0)&&(mouseY <=30)) && play == 1 && son == true){
      Song.pause();
      son = false;
    }
    
    else if(((mouseX >=540)&&(mouseX <=570)) && ((mouseY >=0)&&(mouseY <=30)) && play == 1 && son == false){
      Song.play();
      son = true;
    }
  }
  
   //Fonction Chargement gif, et menu, son victoire, son défaite, musique, son commencement
  
  void Chargement(){
    XPChargement = new Gif(this, "data/xp animation.gif");
    XPChargement.play();
    PacChargement = new Gif(this, "data/pacman chargement.gif");
    PacChargement.play();
    }
  
  
             
  void Menu(){         
    Home = new Gif(this, "data/Background.gif");
    Home.play();         
    }
   
         
         
  void Musique(){
    minim = new Minim(this);
    Song = minim.loadFile ("Pactheme.mp3", 512);
    Song.play();
    }
  
  
  
  void Winsong(){
    minim = new Minim(this);
    victorytheme = minim.loadFile ("winsong.wav", 512);
    victorytheme.play();
    }
  
  
  
  void Deathsong(){
    minim = new Minim(this);
    loosetheme = minim.loadFile ("death.wav", 512);
    loosetheme.play();
  }
  
  
  
  void Beginsong(){
    minim = new Minim(this);
    starttheme = minim.loadFile ("beginning.wav", 512);
    starttheme.play();
  }
  
  
  
  class Mur{
     int x, y;
  Mur(int x, int y) {
    this.x = x;
    this.y = y;
  }
  
  void display() {
    noStroke();
    fill(#0000FF);
    rect(x, y, 30, 30);
  }
  }
  
  
  
  class Monstre{
    int x, y, skin;
  Monstre(int x, int y, int skin) {
    this.x = x;
    this.y = y;
    this.skin = skin;
  }
  
  void display() {
    PImage Monster;
    if(skin == 0){
    Monster = loadImage("data/Monstre.png");
    Monster.resize(30,30);
    image(Monster,x,y);
    }
    if(skin == 1){
    Monster = loadImage("data/Monstre1.png");
    Monster.resize(30,30);
    image(Monster,x,y);
    }
    if(skin == 2){
    Monster = loadImage("data/Monstre2.png");
    Monster.resize(30,30);
    image(Monster,x,y);
    }
    if(skin == 3){
    Monster = loadImage("data/Monstre3.png");
    Monster.resize(30,30);
    image(Monster,x,y);
    }
  }
  }
  
  
  
  class Joueur{
    int x, y;
  Joueur(int x, int y) {
    this.x = x;
    this.y = y;
  }
  
  void display() {
    fill(255, 221, 51);
      pushMatrix();
      translate(x , y);
      if ( skinpacman == 1) { 
        rotate(PI);
      }
      if ( skinpacman == 4) { 
        rotate(HALF_PI);
      }
      if ( skinpacman == 3) { 
        rotate( PI + HALF_PI );
      }
      arc(0, 0, 28, 28, map((millis() % 600), 0, 500, 0, 0.52), map((millis() % 600), 0, 500, TWO_PI, 5.76) );
      popMatrix();
    }
  }
  
  
  
  class Porte{
    int x, y, x1, y1;
  Porte(int x, int y, int x1, int y1) {
    this.x = x;
    this.y = y;
    this.x1 = x1;
    this.y1 = y1;
  }
  
  void display() {
    noStroke();
    fill(#FF0000);
    rect(x, y, x1, y1);
  }
  }
  
  
  
  class Coins{
    int x, y;
  Coins(int x, int y) {
    this.x = x;
    this.y = y;
  }
  
  void display() {
    fill(#FFC81B);
    smooth();
    ellipse(x,y,15,15);
  }
  }
  
  
  
  class Portail{
    int x, y, skin;
  Portail(int x, int y, int skin) {
    this.x = x;
    this.y = y;
    this.skin = skin;
  }
  
  void display() {
    PImage Teleporter;
    if(skin == 0){
    Teleporter = loadImage("data/Portail1.jpg");
    image(Teleporter,x,y);
    }
    if(skin == 1){
    Teleporter = loadImage("data/Portail2.jpg");
    image(Teleporter,x,y);
    }
  }
  }
