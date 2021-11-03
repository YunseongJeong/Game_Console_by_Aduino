#include <LiquidCrystal.h>

LiquidCrystal lcd(44, 45, 46, 47, 48, 49);

int btn_left = 2, btn_right=3, btn_3=4;
int x, y, rotat, blockType;
void sumList(int block_list[16][10], int map_list[16][10]);
int is_crash(int list1[16][10], int list2[16][10]);

int what_height(int map[16][10]){
  // 가장 높이 있는 부분의 좌표를 반환한다. 
  // return : 가장 높이 있는 부분의 좌표 
  // parameter : 배경 데이터  
  for(int i = 15; i>=0; i--){
    for(int j=0; j<10; j++){
      if(map[i][j]) break;
      else return(i);
    }
  }
}

void rotate_block(int block_list[16][10], int map_list[16][10]){
   // 블럭을 x, y를 중심으로 90도 돌린다. 
  // return : 없음
  // parameter : 블럭 데이터, 배경 데이터
  int list[16][10];
    for (int r=0; r<16; r++){
      for (int c=0; c<10; c++){
          list[r][c] = block_list[r][c]; 
      }
    }
    int lastRotat=rotat;
  if (blockType==1){
    if (rotat==0){
      rotat=1;
      block_list[y][x-1]=0;
      block_list[y][x-2]=0;
      block_list[y][x+1]=0;
      block_list[y+1][x]=1;
      block_list[y-1][x]=1;
      block_list[y+2][x]=1;
    }else {
      rotat=0;
      block_list[y][x-1]=1;
      block_list[y][x-2]=1;
      block_list[y][x+1]=1;
      block_list[y+1][x]=0;
      block_list[y-1][x]=0;
      block_list[y+2][x]=0;
    }
  } else if (blockType!=2){
    for (int r=y-1; r<=y+1; r++){
      for (int c=x-1; c<x+1; c++){
        block_list[y][x-1]=list[y+1][x];
        block_list[y][x+1]=list[y-1][x];
        block_list[y+1][x]=list[y][x+1];
        block_list[y-1][x]=list[y][x-1];
        block_list[y+1][x-1]=list[y+1][x+1];
        block_list[y-1][x-1]=list[y+1][x-1];
        block_list[y-1][x+1]=list[y-1][x-1];
        block_list[y+1][x+1]=list[y-1][x+1];
      }
    }
  }

  
    if (is_crash(block_list, map_list)){
      for (int r=0; r<16; r++){
          for (int c=0; c<10; c++){
            block_list[r][c] = list[r][c]; 
          }
      }
      rotat = lastRotat;
    }
}

void random_block(int block_list[16][10]){
  // 랜덤으로 블럭을 소환한다. 
  //return : 없음  
  //parameter : 블럭 데이터
  int num = random(0, 7);
  blockType=num;
  switch(num) {
    case 0:
      block_list[0][5]=1;
      block_list[0][4]=1;
      block_list[1][5]=1;
      block_list[1][6]=1;
      y=0; x=5;
      rotat=0;
      break;
    case 1:
      block_list[0][3]=1;
      block_list[0][4]=1;
      block_list[0][5]=1;
      block_list[0][6]=1;
      y=0; x=5;
      rotat=0;
      break;
    case 2:
      block_list[1][4]=1;
      block_list[0][4]=1;
      block_list[0][5]=1;
      block_list[1][5]=1;
      y=0; x=5;
      break;
    case 3:
      block_list[0][5]=1;
      block_list[0][6]=1;
      block_list[1][5]=1;
      block_list[1][4]=1;
      y=0; x=5;
      rotat=0;
      break;
    case 4:
      block_list[0][5]=1;
      block_list[0][6]=1;
      block_list[0][4]=1;
      block_list[1][5]=1;
      y=0; x=5;
      rotat=0;
      break;
    case 5:
      block_list[0][5]=1;
      block_list[0][6]=1;
      block_list[0][4]=1;
      block_list[1][4]=1;
      y=0; x=5;
      rotat=0;
      break;
    case 6:
      block_list[0][5]=1;
      block_list[0][6]=1;
      block_list[0][4]=1;
      block_list[1][6]=1;
      y=0; x=5;
    rotat=0;
      break;
  }
}



void graphic(int list1[16][10], int list2[16][10]){
  //list1과 list2를 합쳐서 텍스트로 출력한다.
  //return 값은 없다.
  //parameter : 맵 데이터와 블럭 데이터
  byte map1[8];
  for (int r=0; r<8; r++){
    int cbit=0;
    for (int c=0; c<5; c++){
      cbit = cbit*2 + (list1[r][c]||list2[r][c]);
    }
    map1[r] = cbit;
  }
  byte map2[8];
  for (int r=0; r<8; r++){
    int cbit=0;
    for (int c=5; c<10; c++){
      cbit = cbit*2 + (list1[r][c]||list2[r][c]);
    }
    map2[r] = cbit;
  }
  byte map3[8];
  for (int r=8; r<16; r++){
    int cbit=0;
    for (int c=0; c<5; c++){
      cbit = cbit*2 + (list1[r][c]||list2[r][c]);
    }
    map3[r-8] = cbit;
  }
  byte map4[8];
  for (int r=8; r<16; r++){
    int cbit=0;
    for (int c=5; c<10; c++){
      cbit = cbit*2 + (list1[r][c]||list2[r][c]);
    }
    map4[r-8] = cbit;
  }

  lcd.createChar(0, map1);
  lcd.createChar(1, map2);
  lcd.createChar(2, map3);
  lcd.createChar(3, map4);
  lcd.setCursor(0, 0);
  lcd.write(byte(0));
  lcd.setCursor(1, 0);
  lcd.write(byte(1));
  lcd.setCursor(0, 1);
  lcd.write(byte(2));
  lcd.setCursor(1, 1);
  lcd.write(byte(3));
  /*
  Serial.print("////////////////////////////////////////\n");
  for (int r=0; r<16; r++){
    for (int c=0; c<10; c++){
      Serial.print(String(" ")+(list1[r][c]||list2[r][c]));
    }
    Serial.print("\n");
  }
  Serial.print("/////////////////////////////////////////\n");
  */
}

int is_crash(int list1[16][10], int list2[16][10]){  
  // 블럭 데이터와 배경 데이터가 곂치는 부분이 있는지 확인한다. 
  // return : 곂치는 지에 대한 boolean 값 
  // parameter : 블럭 데이터와 배경 데이터  
  int sum1=0, sum2=0;
  for (int r=0; r<16; r++){
    for (int c=0; c<10; c++){
      if (2==list1[r][c]+list2[r][c]){
        return 1;
      }
    }
  }  
  return 0;
}

int drop_block(int block_list[16][10], int map_list[16][10]){
  // 블럭을 한칸 밑으로 이동시키고 밑이 막혔을 때는 그 블럭을 배경에 추가하고 새로운 블럭을 추가한다. 
  // return : 블럭이 밑으로 이동했는지에 대한 boolean 값  
  // 블럭 데이터와 배경 데이터  
  int list[16][10];
  for (int r=0; r<16; r++){
    for (int c=0; c<10; c++){
      list[r][c] = block_list[r][c]; 
    }
  }
  for (int r=14; r>=0; r--){
    for (int c=0; c<10; c++){
      block_list[r+1][c] = block_list[r][c]; 
    }
  }
  for (int c=0; c<10; c++){
    block_list[0][c]=0;
  }
  if (is_crash(block_list, map_list)){
    for (int r=0; r<16; r++){
      for (int c=0; c<10; c++){
        block_list[r][c] = list[r][c]; 
      }
    }
    sumList(block_list, map_list);
    random_block(block_list);
  }else {
    y+=1;
    return 1;
  }
}

void sumList(int block_list[16][10], int map_list[16][10]){
  // 블럭데이터에 있는 블럭을 배경 데이터에 추가하고 블럭 데이터는 초기화한다. 
  // return : 없음 
  // parameter : 블럭데이터와 배경데이터  
  for (int r=0; r<16; r++){
    for (int c=0; c<10; c++){
      if (block_list[r][c])
        map_list[r][c]=block_list[r][c];
      block_list[r][c]=0; 
    }
  }
} 

void move_block(int block_list[16][10], int map_list[16][10], int moveDirection){
  // 횡방향으로 블럭을 이동시킨다.  
  //return : 없음  
  //parameter : 블럭데이터와 배경데이터, 이동 방향 (왼쪽 -1, 오른쪽 +1) 
  int list[16][10];
  for (int r=0; r<16; r++){
    for (int c=0; c<10; c++){
      list[r][c] = block_list[r][c]; 
    }
  }

  for (int r=0; r<16; r++){
     for (int c=(moveDirection==-1?1:9); c!=(moveDirection==-1?10:-1); c=c-moveDirection){
      block_list[r][c+moveDirection] = block_list[r][c];
    }
  }
  
  if (is_crash(block_list, map_list)){
    for (int r=0; r<16; r++){
      for (int c=0; c<10; c++){
        block_list[r][c] = list[r][c]; 
      }
    }
  }else{
    x+=moveDirection;
  }
}

void erase_line(int map_list[16][10], int block_list[16][10]){
  // 한 줄이 꽉 찼는지 검사하고 꽉 찼으면 지운다. 
  //return : 없음  
  //parameter : 배경데이터, 블럭데이터  
  for (int r=14; r>0; r--){
    int sumOfLine=0;
    for (int c=1; c<9; c++){
      sumOfLine+=map_list[r][c];
    }
    if (sumOfLine==8){
      for (int r2=r-1; r2>=0; r2--){
        for (int c=0; c<10; c++){
          map_list[r2+1][c] = map_list[r2][c]; 
        }
      }
      graphic(map_list, block_list);
    }
  }
}



void setup() {
  Serial.begin(9600);
  pinMode(btn_left, INPUT_PULLUP);
  pinMode(btn_right, INPUT_PULLUP);
  pinMode(btn_3, INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
    int map_list[16][10]={
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 
  };
  int block_list[16][10]={
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
  };
  long currentTime, lastTime=millis(); 
  random_block(block_list);
  while(1){
    currentTime = millis();

    erase_line(map_list, block_list);
    
    if (lastTime+1000 <= currentTime){
      drop_block(block_list, map_list);
      graphic(map_list, block_list);
      lastTime=millis();
    }

    if (!digitalRead(btn_left)){
      move_block(block_list, map_list, -1);
      delay(500);
    } else if (!digitalRead(btn_right)){
      move_block(block_list, map_list, 1);
      delay(500);
    }else if (!digitalRead(btn_3)){
      rotate_block(block_list, map_list);
      delay(500);
    } else if (0){
      drop_block(block_list, map_list);
      delay(100);
  }
  }

  while(1){}
}
