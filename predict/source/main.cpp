extern "C" {
#include "cruntime/MainRuntime_inference.h"
#include "cruntime/MainRuntime_parameters.h"
};

#include "Microbit.h"

MicroBit uBit;

#define INTERVAL_OF_GET 80 /* 加速度データの取得間隔 */
#define NUM_OF_VALUES 6  /* 何個のデータを1セットとするか */
#define NUM_OF_CLASS 4  /* 分類するクラス数 */
#define BORDER 93 /* 何％以上の確信度なら採用するか */
#define GROUP_ID 8 /* 無線通信のグループ */

int xValues[NUM_OF_VALUES];
int yValues[NUM_OF_VALUES];
int zValues[NUM_OF_VALUES];

void clear()
{
	int i;
	for(i = 0; i < NUM_OF_VALUES; i++) {
		xValues[i] = 0;
		yValues[i] = 0;
		zValues[i] = 0;
	}
}

void shift()
{
	int i;
	for(i = NUM_OF_VALUES - 1; i > 0; i--) {
		xValues[i] = xValues[i - 1];
		yValues[i] = yValues[i - 1];
		zValues[i] = zValues[i - 1];
	}
}

// for debug
void printList(char *str)
{
	int i;
	for(i=0; i < NUM_OF_VALUES; i ++) {
		uBit.serial.printf("%d,%d,%d,",xValues[i], yValues[i], zValues[i]);
	}
		uBit.serial.printf("%s\r\n",str);
}

int main()
{
	int i = 0;

	void *context = nnablart_mainruntime_allocate_context(MainRuntime_parameters);
	uBit.init();

	uBit.radio.enable();

	uBit.radio.setGroup(GROUP_ID);

	uBit.display.setBrightness(10);
	uBit.serial.printf("Spell Book In:%d Out:%d\r\n", NNABLART_MAINRUNTIME_INPUT0_SIZE, NNABLART_MAINRUNTIME_OUTPUT0_SIZE);	
	uBit.display.print("Book");
	uBit.sleep(2000);

	uBit.display.clear();

	
	while(1)
	{
		// 加速度の値をリストにためておく
		int accX = uBit.accelerometer.getX();
		int accY = uBit.accelerometer.getY();
		int accZ = uBit.accelerometer.getZ();

		shift();
		xValues[0] = accX;
		yValues[0] = accY;
		zValues[0] = accZ;

		// NNにデータを渡してモーションを認識する
		float* input_buf = nnablart_mainruntime_input_buffer(context, 0);
		float* output_buf = nnablart_mainruntime_output_buffer(context, 0);

		for(i = 0; i < NUM_OF_VALUES; i++) {
			*(input_buf + i * 3) = xValues[i];
			*(input_buf + i * 3 + 1) = yValues[i];
			*(input_buf + i * 3 + 2) = zValues[i];
		}
		nnablart_mainruntime_inference(context);

		int max_score = (int) (*output_buf * 100);
		int predict_index = 0;

		for(int i=1; i < NUM_OF_CLASS; ++i){
			int score = (int) (*(output_buf + i) * 100);
			if(max_score < score){
				max_score = score;
				predict_index = i;
			}
		}
		if (max_score < BORDER) predict_index = 0;

		// 
		switch (predict_index){
			case 0:
				// モーションなし
				break;
			case 1:
				printList("motion1");
				uBit.display.print(1);
				uBit.radio.datagram.send("1");
				clear();
				uBit.sleep(2500);
				uBit.display.clear();
				break;
			case 2:
				printList("motion2");
				uBit.radio.datagram.send("2");
				uBit.display.print(2);
				clear();
				uBit.sleep(2500);
				uBit.display.clear();
				break;
			case 3:
				printList("motion3");
				uBit.radio.datagram.send("3");
				uBit.display.print(3);
				clear();
				uBit.sleep(2500);
				uBit.display.clear();
				break;
		}
		// 送信テスト用
		if (uBit.buttonAB.isPressed()) {
			uBit.serial.printf("send 4\r\n");
			uBit.radio.datagram.send("4");
			uBit.display.print(4);
			uBit.sleep(2500);
			uBit.display.clear();
		}
		
		uBit.sleep(INTERVAL_OF_GET);
	}
}
