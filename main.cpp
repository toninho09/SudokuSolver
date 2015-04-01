#include <cstdlib>
#include <iostream>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

struct List{
    int value[10];
    int last;
};

struct LitleBlock{
    int num[9];
};

struct Board{
    struct LitleBlock blocks[9];
};

Board b,b_original;

int index[80];

List initList(){
    struct List l;
    l.last = -1;

    return l;
}

void initBoard(){
    b.blocks[0].num = {0,0,0,0,0,9,0,0,6};
    b.blocks[1].num = {0,0,0,0,0,0,0,4,2};
    b.blocks[2].num = {8,0,6,0,0,0,0,0,0};
    b.blocks[3].num = {0,8,0,0,1,0,0,0,0};
    b.blocks[4].num = {1,0,0,0,0,0,0,0,9};
    b.blocks[5].num = {0,0,0,0,2,0,0,4,0};
    b.blocks[6].num = {0,0,0,0,0,0,2,0,5};
    b.blocks[7].num = {8,3,0,0,0,0,0,0,0};
    b.blocks[8].num = {1,0,0,9,0,0,0,0,0};
    b_original = b;
}

void addList(List &l,int v){
    l.value[l.last+1] = v;
    l.last++;
}

void printList(List &l){
    int i;
    for (i = 0;i<=l.last; i++){
        printf("\nposition:%d value:%d",i,l.value[i]);
    }
}



void removeNumberOnList(List &l,int num){
    int i,j;
    for(i=0 ; i <= l.last;i++){
        if(l.value[i]==num){
            for(j=i;j<=l.last;j++){
                l.value[j]=l.value[j+1];
            }
            l.last--;
        }
    }
}

void removeNumberOnBlock(LitleBlock lb,List &l){
    int i,j;
    for(i=1;i<=9;i++){
        for(j=0;j<9;j++){
            if(lb.num[j] == i){
                removeNumberOnList(l,i);
            }
        }
    }
}

void removeRowSpecificBlock(LitleBlock lb ,int numRow, List &l){
    removeNumberOnList(l,lb.num[(1+(3*(numRow-1)))-1]);
    removeNumberOnList(l,lb.num[(2+(3*(numRow-1)))-1]);
    removeNumberOnList(l,lb.num[(3+(3*(numRow-1)))-1]);
}

int formatNumberLine(int line){
    if(line<=3){
        return line;
    }
    if(line<=6){
        return line-3;
    }
    if(line <=9){
        return line-6;
    }
    return 1;
}

void removeNumberOnRowInBlocks(Board board,int numLine,List &l){
    if(numLine > 0 && numLine <=3){
        removeRowSpecificBlock(board.blocks[0],formatNumberLine(numLine),l);
        removeRowSpecificBlock(board.blocks[1],formatNumberLine(numLine),l);
        removeRowSpecificBlock(board.blocks[2],formatNumberLine(numLine),l);
    }
    if(numLine > 3 && numLine <=6){
        removeRowSpecificBlock(board.blocks[3],formatNumberLine(numLine),l);
        removeRowSpecificBlock(board.blocks[4],formatNumberLine(numLine),l);
        removeRowSpecificBlock(board.blocks[5],formatNumberLine(numLine),l);
    }
    if(numLine > 6 && numLine <=9){
        removeRowSpecificBlock(board.blocks[6],formatNumberLine(numLine),l);
        removeRowSpecificBlock(board.blocks[7],formatNumberLine(numLine),l);
        removeRowSpecificBlock(board.blocks[8],formatNumberLine(numLine),l);
    }

}

void removeColumnsSpecificBlock(LitleBlock lb, int column,List &l){
    removeNumberOnList(l,lb.num[0+(column-1)]);
    removeNumberOnList(l,lb.num[3+(column-1)]);
    removeNumberOnList(l,lb.num[6+(column-1)]);
}

int formatNumberColumn(int column){
    if(column<=3){
        return column;
    }
    if(column<=6){
        return column-3;
    }
    if(column <=9){
        return column-6;
    }
    return 1;
}

void removeNumberOnColumnsInBlocks(Board board,int numColumns,List &l){
    if(numColumns>0 && numColumns <=3){
        removeColumnsSpecificBlock(board.blocks[0],formatNumberColumn(numColumns),l);
        removeColumnsSpecificBlock(board.blocks[3],formatNumberColumn(numColumns),l);
        removeColumnsSpecificBlock(board.blocks[6],formatNumberColumn(numColumns),l);
    }
    if(numColumns>3 && numColumns <=6){
        removeColumnsSpecificBlock(board.blocks[1],formatNumberColumn(numColumns),l);
        removeColumnsSpecificBlock(board.blocks[4],formatNumberColumn(numColumns),l);
        removeColumnsSpecificBlock(board.blocks[7],formatNumberColumn(numColumns),l);
    }
    if(numColumns>6 && numColumns <=9){
        removeColumnsSpecificBlock(board.blocks[2],formatNumberColumn(numColumns),l);
        removeColumnsSpecificBlock(board.blocks[5],formatNumberColumn(numColumns),l);
        removeColumnsSpecificBlock(board.blocks[8],formatNumberColumn(numColumns),l);
    }
}

void fillList(List &l){
    int i;
    l.last = -1;
    for(i =1; i<=9 ;i++){
        l.last++;
        l.value[l.last]=i;
    }
}

void printBloard(){
    printf("\n Calculando sudoku\n");

    printf("\n%d %d %d|%d %d %d|%d %d %d",b.blocks[0].num[0],b.blocks[0].num[1],b.blocks[0].num[2],b.blocks[1].num[0],
           b.blocks[1].num[1],b.blocks[1].num[2],b.blocks[2].num[0],b.blocks[2].num[1],b.blocks[2].num[2]);
    printf("\n%d %d %d|%d %d %d|%d %d %d",b.blocks[0].num[3],b.blocks[0].num[4],b.blocks[0].num[5],b.blocks[1].num[3],
           b.blocks[1].num[4],b.blocks[1].num[5],b.blocks[2].num[3],b.blocks[2].num[4],b.blocks[2].num[5]);
    printf("\n%d %d %d|%d %d %d|%d %d %d",b.blocks[0].num[6],b.blocks[0].num[7],b.blocks[0].num[8],b.blocks[1].num[6],
           b.blocks[1].num[7],b.blocks[1].num[8],b.blocks[2].num[6],b.blocks[2].num[7],b.blocks[2].num[8]);
           printf("\n-----------------");
    printf("\n%d %d %d|%d %d %d|%d %d %d",b.blocks[3].num[0],b.blocks[3].num[1],b.blocks[3].num[2],b.blocks[4].num[0],
           b.blocks[4].num[1],b.blocks[4].num[2],b.blocks[5].num[0],b.blocks[5].num[1],b.blocks[5].num[2]);
    printf("\n%d %d %d|%d %d %d|%d %d %d",b.blocks[3].num[3],b.blocks[3].num[4],b.blocks[3].num[5],b.blocks[4].num[3],
           b.blocks[4].num[4],b.blocks[4].num[5],b.blocks[5].num[3],b.blocks[5].num[4],b.blocks[5].num[5]);
    printf("\n%d %d %d|%d %d %d|%d %d %d",b.blocks[3].num[6],b.blocks[3].num[7],b.blocks[3].num[8],b.blocks[4].num[6],
           b.blocks[4].num[7],b.blocks[4].num[8],b.blocks[5].num[6],b.blocks[5].num[7],b.blocks[5].num[8]);
           printf("\n-----------------");
    printf("\n%d %d %d|%d %d %d|%d %d %d",b.blocks[6].num[0],b.blocks[6].num[1],b.blocks[6].num[2],b.blocks[7].num[0],
           b.blocks[7].num[1],b.blocks[7].num[2],b.blocks[8].num[0],b.blocks[8].num[1],b.blocks[8].num[2]);
    printf("\n%d %d %d|%d %d %d|%d %d %d",b.blocks[6].num[3],b.blocks[6].num[4],b.blocks[6].num[5],b.blocks[7].num[3],
           b.blocks[7].num[4],b.blocks[7].num[5],b.blocks[8].num[3],b.blocks[8].num[4],b.blocks[8].num[5]);
    printf("\n%d %d %d|%d %d %d|%d %d %d",b.blocks[6].num[6],b.blocks[6].num[7],b.blocks[6].num[8],b.blocks[7].num[6],
           b.blocks[7].num[7],b.blocks[7].num[8],b.blocks[8].num[6],b.blocks[8].num[7],b.blocks[8].num[8]);
           printf("\n-----------------");

}

int calcRowNum(int block,int position){
    if(block<3){
        if(position<3){
            return 1;
        }
        if(position<6){
            return 2;
        }
        if(position<9){
            return 3;
        }
    }
    if(block<6){
        if(position<3){
            return 4;
        }
        if(position<6){
            return 5;
        }
        if(position<9){
            return 6;
        }
    }
    if(block<9){
        if(position<3){
            return 7;
        }
        if(position<6){
            return 8;
        }
        if(position<9){
            return 9;
        }
    }
    return 1;
}

int calcColumnNum(int block,int position){
    if(block==0||block==3||block==6){
        if(position==0||position==3||position==6){
            return 1;
        }
        if(position==1||position==4||position==7){
            return 2;
        }
        if(position==2||position==5||position==8){
            return 3;
        }
    }
    if(block==1||block==4||block==7){
        if(position==0||position==3||position==6){
            return 4;
        }
        if(position==1||position==4||position==7){
            return 5;
        }
        if(position==2||position==5||position==8){
            return 6;
        }
    }
    if(block==2||block==5||block==8){
        if(position==0||position==3||position==6){
            return 7;
        }
        if(position==1||position==4||position==7){
            return 8;
        }
        if(position==2||position==5||position==8){
            return 9;
        }
    }

}

int numCalc(int blockNum,int position,int numInList){

    if(b_original.blocks[blockNum].num[position] == 0){
        b.blocks[blockNum].num[position] =0;
        List l = initList();
        fillList(l);
        removeNumberOnBlock(b.blocks[blockNum],l);
        removeNumberOnRowInBlocks(b,calcRowNum(blockNum,position),l);
        removeNumberOnColumnsInBlocks(b,calcColumnNum(blockNum,position),l);
        //printList(l);
        if(l.last>=numInList){
            return l.value[numInList];
        }else{
            //printf("\nNao encontrou o valor em blocko %d, posicao %d",blockNum,position);
            return 0;
        }
    }
    return b.blocks[blockNum].num[position];

}
int calcRowByPosicion(int position){
    return (int)position/9;
}
int calcColumnsByPosition(int position){
    return position % 9;
}
int calcBlockByPosition(int position){
    if(position == 0||position == 1||position == 2||
       position == 9||position == 10||position == 11||
       position == 18||position == 19||position == 20){
        return 1;
       }
    if(position == 3||position == 4||position == 5||
       position == 12||position == 13||position == 14||
       position == 21||position == 22||position == 23){
        return 2;
       }
    if(position == 6||position == 7||position == 8||
       position == 15||position == 16||position == 17||
       position == 24||position == 25||position == 26){
        return 3;
       }
    if(position == 27||position == 28||position == 29||
       position == 36||position == 37||position == 38||
       position == 45||position == 46||position == 47){
        return 4;
       }
    if(position == 30||position == 31||position == 32||
       position == 39||position == 40||position == 41||
       position == 48||position == 49||position == 50){
        return 5;
       }
    if(position == 33||position == 34||position == 35||
       position == 42||position == 43||position == 44||
       position == 51||position == 52||position == 53){
        return 6;
       }
    if(position == 54||position == 55||position == 56||
       position == 63||position == 64||position == 65||
       position == 72||position == 73||position == 74){
        return 7;
       }
    if(position == 57||position == 58||position == 59||
       position == 66||position == 67||position == 68||
       position == 75||position == 76||position == 77){
        return 8;
       }
    if(position == 60||position == 61||position == 62||
       position == 69||position == 70||position == 71||
       position == 78||position == 79||position == 80){
        return 9;
       }
}

int calcNumbyPosition(int position){

    if(position == 0||position == 3||position == 6||
       position == 27||position == 30||position == 33||
       position == 54||position == 57||position == 60){
        return 1;
       }
    if(position == 1||position == 4||position == 7||
       position == 28||position == 31||position == 34||
       position == 55||position == 58||position == 61){
        return 2;
       }
    if(position == 2||position == 5||position == 8||
       position == 29||position == 32||position == 35||
       position == 56||position == 59||position == 62){
        return 3;
       }
    if(position == 9||position == 12||position == 15||
       position == 36||position == 39||position == 42||
       position == 63||position == 66||position == 69){
        return 4;
       }
    if(position == 10||position == 13||position == 16||
       position == 37||position == 40||position == 43||
       position == 64||position == 67||position == 70){
        return 5;
       }
    if(position == 11||position == 14||position == 17||
       position == 38||position == 41||position == 44||
       position == 65||position == 68||position == 71){
        return 6;
       }
    if(position == 18||position == 21||position == 24||
       position == 45||position == 48||position == 51||
       position == 72||position == 75||position == 78){
        return 7;
       }
    if(position == 19||position == 22||position == 25||
       position == 46||position == 49||position == 52||
       position == 73||position == 76||position == 79){
        return 8;
       }
    if(position == 20||position == 23||position == 26||
       position == 47||position == 50||position == 53||
       position == 74||position == 77||position == 80){
        return 9;
       }
}
int main()
{
    int x;
    for(x=0;x<80;x++){
        index[x]=0;
    }
    initBoard();
    printBloard();
    int i,j,numInList,block,blockPosition;
    numInList = 0;
    for(i=0;i<81;i++){
        block = calcBlockByPosition(i)-1;
        blockPosition = calcNumbyPosition(i)-1;
        if(i==47){
            i=47;
        }
        if(b_original.blocks[calcBlockByPosition(i)-1].num[calcNumbyPosition(i)-1] != 0){
            if(index[i] != 0){
                index[i]=0;
                if(i>=1){
                    index[i-1]++;
                    i-=2;
                }
            }
            continue;
        }
        b.blocks[calcBlockByPosition(i)-1].num[calcNumbyPosition(i)-1] = numCalc((calcBlockByPosition(i)-1),(calcNumbyPosition(i)-1),index[i]);
        if(b.blocks[calcBlockByPosition(i)-1].num[calcNumbyPosition(i)-1] == 0){
            if(i>=1){
                index[i]=0;
                index[i-1]++;
                i-=2;
            }
        }
        system("cls");
        printBloard();
    }
    printBloard();
    return 0;
}
