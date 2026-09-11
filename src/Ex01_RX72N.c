/***********************************************************************
*
*  FILE        : Ex01_RX72N.c
*  DATE        : 2024-12-17
*  DESCRIPTION : Main Program
*
*  NOTE:THIS IS A TYPICAL EXAMPLE.
*
***********************************************************************/
#include "r_can_rx_if.h"
#include "r_cmt_rx_if.h" // 追加: R_CMT_CreatePeriodic 関数の宣言
#include "r_can_rx_pinset.h" // 追加: R_CAN_PinSet_CAN1 関数の宣言

/*----------------------------------------------------------------------
    プロトタイプ宣言
----------------------------------------------------------------------*/
//メイン関数宣言
int main(void);

//タイマ割り込み関数宣言
void INT_Excep_CMT0_CMI0(void *pdata); // 修正: void *pdata を追加

//can初期化宣言
void CAN1Init(void);

//cmt初期化宣言
void CMT0_init(void);

/*----------------------------------------------------------------------
    メイン関数
----------------------------------------------------------------------*/
int main(void) {
    // CAN初期化
    CAN1Init();

    // CMT初期化
    CMT0_init();

    //割込待機
    while(1) {
      }
}

/*----------------------------------------------------------------------
    タイマ割り込み関数（定周期割り込み）
----------------------------------------------------------------------*/
void INT_Excep_CMT0_CMI0(void *pdata) { // 修正: void *pdata を追加
    //CANalyzerに送信する値の変数を定義
    char schar;
    unsigned char uchar;
    short sshort;
    unsigned short ushort;
    int sint;
    unsigned int uint;
    long slong;
    unsigned long ulong;

    //CANalyzerに送信する値を変数に格納
    schar = 120;	//120; 初期値
    uchar = 120;	//120; 初期値
    sshort = 40;
    ushort = 55;	//55; 初期値
    sint = -105;	//-105; 初期値
    uint = 75;		//75; 初期値
    slong = -100;	//-100; 初期値
    ulong = 10;		//10; 初期値

    //値を変えたら
    //Shift + 5 でデバッグ停止
    //Ctrl + Shift + p でコマンドパレットを開く
    //[キャッシュの削除と再構成]を選択
    //F7でビルドし、エラーがないことを確認
    //F5でデバッグ開始
    //再度F5でデバッグを進行

    // CAN送信データ設定　送信のみ
    can_frame_t frame;

    frame.id = 0x100;
    frame.dlc = 8;
    frame.data[0] = schar;
    frame.data[1] = uchar;
    frame.data[2] = (unsigned char)(sshort >> 8);
    frame.data[3] = (unsigned char)sshort;
    frame.data[4] = (unsigned char)(ushort >> 8);
    frame.data[5] = (unsigned char)ushort;
    frame.data[6] = (unsigned char)(sint >> 8);
    frame.data[7] = (unsigned char)sint;
    R_CAN_TxSet(1, 0, 1, &frame, DATA_FRAME); //メールボックスに格納

    frame.id = 0x101;
    frame.dlc = 8;
    frame.data[0] = (unsigned char)(uint >> 8);
    frame.data[1] = (unsigned char)uint;
    frame.data[2] = (unsigned char)(slong >> 24);
    frame.data[3] = (unsigned char)(slong >> 16);
    frame.data[4] = (unsigned char)(slong >> 8);
    frame.data[5] = (unsigned char)slong;
    R_CAN_TxSet(1, 0, 2, &frame, DATA_FRAME); //メールボックスに格納

    frame.id = 0x102;
    frame.dlc = 8;
    frame.data[0] = (unsigned char)(ulong >> 24);
    frame.data[1] = (unsigned char)(ulong >> 16);
    frame.data[2] = (unsigned char)(ulong >> 8);
    frame.data[3] = (unsigned char)ulong;
    R_CAN_TxSet(1, 0, 3, &frame, DATA_FRAME); //メールボックスに格納

    // メールボックスをCAN送信
    R_CAN_Tx(1, 0, 1);
    R_CAN_Tx(1, 0, 2);
    R_CAN_Tx(1, 0, 3);
}

/*----------------------------------------------------------------------
    CAN初期化関数
----------------------------------------------------------------------*/
void CAN1Init(void) {
    //ボーレート設定　500kbps（変更する場合はリセットモードでR_CAN_SetBitrate）式：(PCLKB)60MHz / ((6 - 1) + 1) * (14 + 5 + 1) = 500kbps :: 20tqtot, サンプルポイント = (1+14)/20 = 75%
    can_bitrate_config_t p_cfg;
    p_cfg.BRP = 6; // 6
    p_cfg.TSEG1 = 14; // 14Tq
    p_cfg.TSEG2 = 5; // 5Tq 
    p_cfg.SJW = 1; // 1Tq

    //CAN初期化関数
    R_CAN_Create(1, 0, p_cfg, NULL, NULL, NULL, NULL, NULL);

    //CANピン設定
    R_CAN_PinSet_CAN1();

    //CANポート設定
    R_CAN_PortSet(1, ENABLE);

    //CAN動作モード設定　コメントは参考
    // R_CAN_Control(1, EXITSLEEP_CANMODE); //スリープモード解除
    // R_CAN_Control(1, ENTERSLEEP_CANMODE); //スリープモードへ遷移
    // R_CAN_Control(1, RESET_CANMODE); //リセットモードへ遷移
    // R_CAN_Control(1, HALT_CANMODE); //Haltモードへ遷移
    R_CAN_Control(1, OPERATE_CANMODE); //オペレーションモードへ遷移
}

/*----------------------------------------------------------------------
    コンペアマッチタイマ初期化関数 CMT0
----------------------------------------------------------------------*/

void CMT0_init(void) {
    // 割り込みチャネル
    uint32_t channel;
    // 周期割り込みの設定
    R_CMT_CreatePeriodic(1000, INT_Excep_CMT0_CMI0, &channel);
}