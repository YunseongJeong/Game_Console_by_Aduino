#include <LiquidCrystal.h>

int btn_left = 2, btn_right=3, btn_3=4;
int x, y;
void sumList(int block_list[16][10], int map_list[16][10]);

int what_height(int map[16][10]){
  // 쌓인 테트리스의 높이를 구한다.
  // return 값은 행의 값을 출력한다.
  // parameter : 맵 데이터
  for(int i = 15; i>=0; i--){
    for(int j=0; j<10; j++){
      if(map[i][j]) break;
      else return(i);
    }
  }
}

void rotate_block(int block_list[16][10], int map_list[16][10]){
  
}

void random_block(int block_list[16][10]){
  //랜덤으로 7가지 블럭중 하나를 소환한다.
  //return 값은 없다.
  //parameter 블럭 데이터
  int num = random(1, 8);
  switch(num) {
    case 1:
      block_list[0][5]=1;
      block_list[0][4]=1;
      block_list[1][5]=1;
      block_list[1][6]=1;
      y=0; x=5;
      break;
    case 2:
      block_list[0][3]=1;
      block_list[0][4]=1;
      block_list[0][5]=1;
      block_list[0][6]=1;
      y=0; x=5;
      break;
    case 3:
      block_list[1][4]=1;
      block_list[0][4]=1;
      block_list[0][5]=1;
      block_list[1][5]=1;
      y=0; x=5;
      break;
    case 4:
      block_list[0][5]=1;
      block_list[0][6]=1;
      block_list[1][5]=1;
      block_list[1][4]=1;
      y=0; x=5;
      break;
    case 5:
      block_list[0][5]=1;
      block_list[0][6]=1;
      block_list[0][4]=1;
      block_list[1][5]=1;
      y=0; x=5;
      break;
    case 6:
      block_list[0][5]=1;
      block_list[0][6]=1;
      block_list[0][4]=1;
      block_list[1][4]=1;
      y=0; x=5;
      break;
    case 7:
      block_list[0][5]=1;
      block_list[0][6]=1;
      block_list[0][4]=1;
      block_list[1][6]=1;
      y=0; x=5;
      break;
  }
}


void graphic(int list1[16][10], int list2[16][10]){
  //list1과 list2를 합쳐서 텍스트로 출력한다.
  //return 값은 없다.
  //parameter : 맵 데이터와 블럭 데이터 
  Serial.print("////////////////////////////////////////\n");
  for (int r=0; r<16; r++){
    for (int c=0; c<10; c++){
      Serial.print(String(" ")+(list1[r][c]||list2[r][c]));
    }
    Serial.print("\n");
  }
  Serial.print("/////////////////////////////////////////\n");
}

int is_crash(int list1[16][10], int list2[16][10]){  
  // list1과 list2에 곂치는 픽셀이 있나 검사한다.
  // return : 없음
  // parameter : 맵 데이터와 블럭 데이터 
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
  // list에 저장된 block을 밑으로 떨어트린다.(떨어트렸을때 충돌이 없으면) 
  // return 충돌 했을 때 0, 충돌하지 않았을 때 1 
  // 블럭이 저장된 list , maplist
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
  //block list에 있는block을 map_list로 옮긴다.
  // return 없음
  // parameter 블럭 데이터, 맵 데이터 
  for (int r=0; r<16; r++){
    for (int c=0; c<10; c++){
      if (block_list[r][c])
        map_list[r][c]=block_list[r][c];
      block_list[r][c]=0; 
    }
  }
} 

void move_block(int block_list[16][10], int map_list[16][10], int moveDirection){
  //block을 횡 방향으로 움직인다.
  //return 없음
  //parameter 블럭 데이터, 맵 데이터, 방향 (왼쪽 -1)(오른쪽 1)
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
  //한줄이 다 1로 꽉차면 그 줄을 지운다.
  //return 없음
  //parameter 맵 데이터, 블럭 데이터
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
    }
  }

  while(1){}
}
