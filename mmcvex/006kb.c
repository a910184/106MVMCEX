
 //																專題七

 //															電子計算機(輪詢式)
#include "ASA_Lib.h"

void ASAKB (char keynum,char *a,char *b);
void carry(char number,char sign,long int *a);
void caulate (long int nf,char sign,char number,long int *a,long int *b);
void print(long int nf,long int ans,char number,char sign,char *g);

// ----2017-07-10-by-Hen--------------------------------------------------------

int main(void){
	// M128initial
	ASA_M128_set();
	// 變數宣告區
	char s=0,x,y;
	// 累進值暫存器
	long int z=0;
	// 結果暫存器
	long int ans=0;
	// 7S00顯示用矩陣
	char Q[4]={0,0,0,48};
	// 設定7S00無閃爍無小數點
	ASA_7S00_set(2,200,0,0,0);
	_delay_ms(100);
	// 設定KB00輸出ASCII碼
	ASA_KB00_set(1,200,0x01,0,1);
	_delay_ms(100);
	// 7S00顯示"    0"
	ASA_7S00_put(2,0,4,Q);
	_delay_ms(100);
	/*
	注意!
	------------------------------KB00跟7S00ID旋鈕請轉到不同ID----------------------------------
	------------------------------KB00跟7S00ID旋鈕請轉到不同ID----------------------------------
	------------------------------KB00跟7S00ID旋鈕請轉到不同ID----------------------------------
	------------------------------0號為預設保留通道 請不要使用----------------------------------
	------------------------------0號為預設保留通道 請不要使用----------------------------------
	------------------------------0號為預設保留通道 請不要使用----------------------------------
	謝謝你的注意
	 */


	while(1){
		// 若無輸入 則繼續取得輸入鍵號
		while(s==0){
			// 取得輸入鍵號
			ASA_KB00_get(1,100,1,&s);
		}
		// 若7S00顯示"----"  則不接受"清除"以外輸入
		if(Q[0]==45 && Q[1]==45 && Q[2]==45 && Q[3]==45){
			while(s!=65){
				ASA_KB00_get(1,100,1,&s);
			}
		}
		// 測試鍵號解譯模組函式
		ASAKB(s,&x,&y);
		// 按下清除鍵
		if(x==10&&y==6){
			// 清除累進值暫存器與結果暫存器
			z=ans=0;
		}
		// 累加進位器函式
		carry(x,y,&z);
		// 運算器函式
		caulate(z,y,x,&ans,&z);
		// 顯示處理函式
		print(z,ans,x,y,Q);
		// 呼叫7S00顯示用函示
		ASA_7S00_put(2,0,4,Q);
		// 延遲100ms防彈跳
		_delay_ms(100);
		// 若尚未放開按鍵 則繼續取得輸入鍵號
		while(s!=0){
			ASA_KB00_get(1,100,1,&s);
		}
	}
}

void ASAKB (char keynum,char *a,char *b){
	// 數值旗標兼數值 ,  符號旗標兼等號or四則or清除旗標
	char number=0,sign=0;
	switch(keynum){
		case 70:{number=10;	sign=1;	break;}	//F +
		case 69:{number=10;	sign=2;	break;}	//E -
		case 68:{number=10;	sign=3;	break;}	//D *
		case 67:{number=10;	sign=4;	break;}	//C /
		case 66:{number=10;	sign=5;	break;}	//B =
		case 65:{number=10;	sign=6;	break;}	//A 清除
		case 48:{number=0;	sign=0;	break;}	//0
		case 49:{number=1;	sign=0;	break;}	//1
		case 50:{number=2;	sign=0;	break;}	//2
		case 51:{number=3;	sign=0;	break;}	//3
		case 52:{number=4;	sign=0;	break;}	//4
		case 53:{number=5;	sign=0;	break;}	//5
		case 54:{number=6;	sign=0;	break;}	//6
		case 55:{number=7;	sign=0;	break;}	//7
		case 56:{number=8;	sign=0;	break;}	//8
		case 57:{number=9;	sign=0;	break;}	//9
	}
	*a=number;
	*b=sign;
}

void carry(char number,char sign,long int *a){
	// 前次輸入為符號旗標
	static int dflag=0;
	// 累進值暫存器
	static long int nf=0;
	// 若輸入為符號
	if(number==10){
		// 輸入為"清除"鍵
		if(sign==6){
			// 清除"前次輸入為符號旗標
			dflag=0;
			// 累進暫存器歸零
			nf=0;
		}
		// 輸入為"清除"鍵以外的符號
		else{
			// 豎起"前次輸入為符號旗標"
			dflag=1;
		}
	}
	// 若輸入為數值
	else{
		// 若"前次輸入為符號旗標"為豎起狀態 且本次輸入為數值 則清空累進暫存器
		if(dflag==1){
			// 累進暫存器歸零
			nf=0;
			// 清除"前次輸入為符號旗標
			dflag=0;
		}
		// 累進暫存器=累進暫存器×10+新輸入整數
		nf=(nf*10+number);
		// 累進值=累進暫存器
		*a=nf;
	}
}

void caulate (long int nf,char sign,char number,long int *a,long int *b){
	// 四則運算子暫存器
	static int cau;
	// 運算元暫存器一
	static long int num1;
	// 運算元暫存器二
	static long int num2;
	//等號旗標  運算子旗標
	static char e=0,o=0;
	// 若輸入為符號
	if(number==10){
		// 輸入為"清除"鍵
		if(sign==6){
			// 清除所有暫存器與旗標
			cau=0;	num1=0;	num2=0;	e=0; o=0;
		}
		// 輸入為"等號"鍵
		else if(sign==5){
			// 豎起等號旗標
			e=1;
			// 將累進值放入運算元暫存器二
			num2=nf;
			switch(cau){
				//四則運算子暫存器為空 也就是按完數字接著按等號的富有冒險精神的勇者
				case 0:{
					// 將累進值放入結果暫存器
					*a=nf;
					break;
				}
				// 四則運算子暫存器為"+"
				case 1:{
					// 計算結果 並放入結果暫存器
					*a=num1+num2;
					// 將計算結果放入運算元暫存器一 等待接收到第二次等號 再進行一次計算
					num1=*a;
					break;
				}
				// 四則運算子暫存器為"-"
				case 2:{
					// 計算結果並放入結果暫存器
					*a=num1-num2;
					// 將計算結果放入運算元暫存器一 等待接收到第二次等號 再進行一次計算
					num1=*a;
					break;
				}
				// 四則運算子暫存器為"*"
				case 3:{
					// 計算結果並放入結果暫存器
					*a=num1*num2;
					// 將計算結果放入運算元暫存器一 等待接收到第二次等號 再進行一次計算
					num1=*a;
					break;
				}
				// 四則運算子暫存器為"/"
				case 4:{
					// 若除數為0
					if(num2==0){
						// 讓結果暫存器炸掉
						*a=10000;
					}
					else{
						// 計算結果並放入結果暫存器
						*a=num1/num2;
						// 將計算結果放入運算元暫存器一 等待接收到第二次等號 再進行一次計算
						num1=*a;
					}
					break;
				}
			}
		}
		// 輸入為四則運算子
		else {
			// 若等號旗標與運算子旗標皆未豎起
			if(e==0 && o==0){
				switch(cau){
					//四則運算子暫存器為空 也就是第一次輸入四則運算子
					case 0:{
						// 將累進值放入運算元暫存器一
						num1=nf;
						break;
					}
					// 四則運算子暫存器為"+" 也就是第二次以上輸入運算子(非連續輸入)
					case 1:{
						// 將累進值放入運算元暫存器二
						num2=nf;
						// 計算結果並放入結果暫存器
						*a=num1+num2;
						// 將計算結果放入運算元暫存器一
						num1=*a;
						// 將計算結果放入累進值
						*b=*a;
						break;}
					// 四則運算子暫存器為"-" 也就是第二次以上輸入運算子(非連續輸入)
					case 2:{
						// 將累進值放入運算元暫存器二
						num2=nf;
						// 計算結果並放入結果暫存器
						*a=num1-num2;
						// 將計算結果放入運算元暫存器一
						num1=*a;
						// 將計算結果放入累進值
						*b=*a;
						break;
					}
					// 四則運算子暫存器為"*" 也就是第二次以上輸入運算子(非連續輸入)
					case 3:{
						// 將累進值放入運算元暫存器二
						num2=nf;
						// 計算結果並放入結果暫存器
						*a=num1*num2;
						// 將計算結果放入運算元暫存器一
						num1=*a;
						// 將計算結果放入累進值
						*b=*a;
						break;
					}
					// 四則運算子暫存器為"/" 也就是第二次以上輸入運算子(非連續輸入)
					case 4:{
						// 將累進值放入運算元暫存器二
						num2=nf;
						// 計算結果並放入結果暫存器
						*a=num1/num2;
						// 將計算結果放入運算元暫存器一
						num1=*a;
						// 將計算結果放入累進值
						*b=*a;
						break;
					}
				}
				// 將四則運算子放入四則運算子暫存器
				cau=sign;
				// 豎起運算子旗標
				o=1;
			}
			// 若等號旗標與運算子旗標其中之一豎起
			else{
				// 運算子旗標為豎起 可能正在連續輸入運算子
				if(o==1){
					// 將四則運算子放入四則運算子暫存器
					cau=sign;
				}
				// 等號旗標為豎起 也就是等號後接著輸入運算子
				if(e==1){
					// 將計算結果放入運算元暫存器一
					num1=*a;
					// 將計算結果放入累進值
					*b=*a;
					// 將四則運算子放入四則運算子暫存器
					cau=sign;
					// 清除等號旗標
					e=0;
					// 豎起運算子旗標
					o=1;
				}
			}
		}
	}
	// 若輸入為數值
	if(number!=10){
		// 清除運算子旗標
		o=0;
		// 若等號旗標豎起
		if(e==1){
			// 清除所有暫存器與旗標
			cau=0; num1=0; num2=0; e=0; o=0;
		}
	}
}

void print(long int nf,long int ans,char number,char sign,char *g){
	// 顯示值, 商數, 餘數
	long int print,a,b;
	// 顯示值位數
	char prinum=0;
	// 負數旗標
	int c=0;
	// 7S00顯示用矩陣清空
	*g=*(g+1)=*(g+2)=*(g+3)=0;
	// 若輸入為等號 則顯示計算結果
	if(sign==5){print=ans;}
	// 若輸入為"清除" 則顯示0
	else if(number==10&&sign==6){print=0;}
	// 非以上情況 則顯示累進值
	else{print=nf;}
	// 若顯示值為0 則7S00顯示用矩陣歸零("   0")
	if(print==0){ *g=*(g+1)=*(g+2)=0;*(g+3)=48; }
	// 若顯示值不為0
	else{
		// 若顯示值為正數
		if(print>0){
			// 若顯示值為十位數以上
			if(print/10){
				// 若顯示值為百位數以上
				if(print/100){
					// 若顯示值為千位數以上  顯示值位數為4位數
					if(print/1000)	prinum=4;
					// 否則顯示值位數為3位數
					else prinum=3;
				}
				// 否則顯示值位數為2位數
				else prinum=2;
			}
			// 否則顯示值位數為1位數
			else prinum=1;
		}
		// 若顯示值為負數
		if(print<0){
			// 將顯示值轉為正數較容易處理
			print=(-1)*print;
			// 豎起負數旗標
			c=1;
			// 若顯示值為十位數以上
			if(print/10){
				// 若顯示值為百位數以上
				if(print/100) {
					// 若顯示值為千位數以上 將負數旗標設為爆掉 因為負數無法顯示四位數
					if(print/1000) c=2;
					// 否則顯示值位數為3位數
					else prinum=3;
				}
				// 否則顯示值位數為2位數
				else prinum=2;
			}
			// 否則顯示值位數為1位數
			else prinum=1;
		}
		// 將顯示值放入商數, 餘數=0
		a=print;b=0;
		// i從3漸減到4-prinuml
		for(int i=3;i>=4-prinum;i--){
			// 餘數=商數-(商數/10)*10;
			b=a-(a/10)*10;
			// 商數=(商數-餘數)/10;
			a=(a-b)/10;
			// 7S00顯示用矩陣[i] = 餘數的ASCII碼
			*(g+i)=b+48;
			// 若負數旗標為豎起  7S00顯示用矩陣[i-1]顯示"-"
			if(c==1) *(g+i-1)=45;
		}
		// 若數值溢位 顯示"----"
		if(a!=0||c==2)*g=*(g+1)=*(g+2)=*(g+3)=45;
	}
}
