/* Generated configuration header file - do not edit */
/***********************************************************************************************************************
* 免責事項
* このソフトウェアはルネサス エレクトロニクス株式会社によって提供され、ルネサス製品での使用のみを目的としています。他の用途には
* 使用できません。このソフトウェアはルネサス エレクトロニクス株式会社の所有物であり、著作権法を含むすべての適用法によって保護されています。
* このソフトウェアは「現状のまま」提供され、ルネサスはこのソフトウェアに関して、明示的、黙示的、または法定のいかなる保証も行いません。
* 商品性、特定の目的への適合性、および非侵害についての保証を含むがこれに限定されないすべての保証は明示的に否認されます。
* 法律で禁止されていない限り、ルネサス エレクトロニクス株式会社またはその関連会社は、このソフトウェアに関連するいかなる理由による
* 直接的、間接的、特別、偶発的、または結果的損害についても責任を負いません。たとえルネサスまたはその関連会社がそのような損害の可能性を
* 知っていたとしても同様です。
* ルネサスは、通知なしにこのソフトウェアに変更を加える権利、およびこのソフトウェアの提供を中止する権利を留保します。
* このソフトウェアを使用することにより、以下のリンクにアクセスして追加の条件に同意したものとみなされます。
* http://www.renesas.com/disclaimer
*
* 著作権 (C) 2015 ルネサス エレクトロニクス株式会社。無断複写・転載を禁じます。
***********************************************************************************************************************/
/***********************************************************************************************************************
* ファイル名    : r_can_rx_config.h
* 説明          : RX CAN FITコードを設定します。
************************************************************************************************************************
* 履歴 : DD.MM.YYYY バージョン 説明
*         : 02.01.2015 1.10    64M、71M、65N用。
*         : 30.10.2015 2.02    FIT更新、新しいR_CAN_Createインターフェース。
*         : 03.03.2016 2.10    65N追加。
*         : 30.01.2017 2.11    65N 2MBでテスト済み。（コメントのみ変更。）
*         : 14.08.2017 2.12    65N 2MB用リリースバージョン。r_can_rx.cのバグ修正。
*         : 27.04.2018 2.13    - RX66T追加
*         : 26.09.2018 2.13    Smart Configurator用にr_can_rx_config.hを改訂
*         : 08.01.2019 2.15    - RX72T追加
*         : 30.04.2019 3.10    - RX72M追加
*         : 30.12.2019 3.20    - RX66N、RX72Nのサポートを追加。
*         :                    - GSCEコーディングスタンダードRev.6.00に準拠するよう修正。
*         : 13.06.2020 4.00    - CAN FIFOのサポートを追加。
*         :                    - ピン設定に関連するマクロを削除。
*         :                    - STB/ENポート/ピンのマクロ値の誤った括弧を削除。
*         : 01.04.2021 5.00    - 異なるチャネルに異なるビットレートを設定するサポートを追加。
*         : 08.09.2023 5.50    - FRAME_ID_MODEの各値の説明を追加。
***********************************************************************************************************************/
#ifndef CAN_CONFIG_HEADER_FILE
#define CAN_CONFIG_HEADER_FILE

/* Includes board and MCU related header files. */
#include "platform.h"

/***********************************************************************************************************************
Configuration Options
***********************************************************************************************************************/
/* CANの割り込みを使用する場合は0に設定します。CANのメールボックスをポーリングして送受信メッセージを確認する場合は1に設定します。 */
#define USE_CAN_POLL        (0)   /* 1 polled mode, 0 use interrupts (=default). */

/* 送信FIFO割り込み生成タイミング制御:
    0は送信が完了するたびに（デフォルト）、
    1は送信が完了して送信FIFOが空になるとき。 */
#define CAN_CFG_TXFIFO_INT_GEN_TIMING        (0) 

/* 受信FIFO割り込み生成タイミング制御:
    0は受信が完了するたびに（デフォルト）、
    1は受信が完了して受信FIFOがバッファ警告になるとき。 */
#define CAN_CFG_RXFIFO_INT_GEN_TIMING        (0)

/* Level */
#define CAN0_INT_LVL        (2)
#define CAN1_INT_LVL        (2)
#define CAN2_INT_LVL        (2)

/**********************************************************************************************************************
 * ドライバのCAN IDタイプを選択します。11ビットまたは29ビットのIDの使用を選択します。FRAME_ID_MODEは、STD_ID_MODE、EXT_ID_MODE、
 * またはMIXED_ID_MODEに設定できます。最初の2つの設定は、そのIDモードに属するAPI関数のみを有効にします。混合モードに設定すると、
 * 全てのAPIが利用可能になります。
 *    STD_ID_MODE      すべてのメールボックス（FIFOメールボックスを含む）は標準IDのみを処理します。
 *    EXT_ID_MODE      すべてのメールボックス（FIFOメールボックスを含む）は拡張IDのみを処理します。
 *    MIXED_ID_MODE    すべてのメールボックス（FIFOメールボックスを含む）は標準IDと拡張IDの両方を処理します。
 * MIXED_ID_MODEは、標準フレームと拡張フレームの両方がネットワークに存在する場合に使用する必要があります。そうしないと、
 * CANハードウェアによってメッセージが誤解される可能性があります。1つだけ選択してください。再度、標準および拡張CANフレームが
 * バス上に存在する場合はMIXED_ID_MODEを使用してください。そうしないと、予期しないデータが発生する可能性があります。
 * #define FRAME_ID_MODE   STD_ID_MODE       11ビットCAN ID。デフォルト
 * #define FRAME_ID_MODE   EXT_ID_MODE       29ビットCAN ID。
 * #define FRAME_ID_MODE   MIXED_ID_MODE
 ***********************************************************************************************************************/
#define FRAME_ID_MODE   (STD_ID_MODE)

/**********************************************************************************************************************
 * ポート設定 *
 * CANポート設定マクロで使用されるCAN0 RXおよびTXピンを構成します。
 * RXはバージョンによって最大3つのCANチャネルを持つことができます。
 * デバイスのポート可用性についてはRXグループユーザーマニュアルを確認してください。
 * ここで定義されたピンは、CANチャネルが使用されているかどうかに関係なく、すべてのサポートされているデバイスとのドライバ互換性を確保するために定義されています。
 * 使用されていないCANチャネルのためにここで定義されたピンは無視され、他の用途に利用可能なままです。
 ***********************************************************************************************************************/
#define CAN_USE_CAN0    (0)

#define CAN_USE_CAN1    (1)

#define CAN_USE_CAN2    (0)


/**********************************************************************************************************************
 * スタンバイおよびイネーブルピンを持つCANトランシーバICは、次の定義を使用してこのドライバでサポートできます。
 * ポート番号、ビット番号、およびアクティブレベルを例のように設定します。
 ***********************************************************************************************************************/
#define CAN_USE_CAN0_STANDBY_ENABLE_PINS (0)
#if (CAN_USE_CAN0_STANDBY_ENABLE_PINS == 1)
/* Configure CAN0 STBn GPIO output pin. */
    #define CAN0_TRX_STB_PORT       0
    #define CAN0_TRX_STB_PIN        0
    #define CAN0_TRX_STB_LVL        0   /* Choose High or Low active state for CAN Transceiver standby pin. */

    /* Configure CAN0 EN GPIO output pin. */
    #define CAN0_TRX_ENABLE_PORT    0
    #define CAN0_TRX_ENABLE_PIN     0
    #define CAN0_TRX_ENABLE_LVL     0   /* Choose High or Low active state for CAN Transceiver standby pin. */
#endif

#define CAN_USE_CAN1_STANDBY_ENABLE_PINS (0)
#if (CAN_USE_CAN1_STANDBY_ENABLE_PINS == 1)
    /* Configure CAN1 STBn GPIO output pin.
    Output. High = not standby. */
    #define CAN1_TRX_STB_PORT       0
    #define CAN1_TRX_STB_PIN        0
    #define CAN1_TRX_STB_LVL        0   /* Choose High or Low active state for CAN Transceiver standby pin. */

    /* Configure CAN1 EN GPIO output pin. */
    #define CAN1_TRX_ENABLE_PORT    0
    #define CAN1_TRX_ENABLE_PIN     0
    #define CAN1_TRX_ENABLE_LVL     0   /* Choose High or Low active state for CAN Transceiver standby pin. */
#endif

#define CAN_USE_CAN2_STANDBY_ENABLE_PINS (0)
#if (CAN_USE_CAN2_STANDBY_ENABLE_PINS == 1)
    /* Configure CAN2 STB GPIO output pin.
    Output. High = not standby. */
    #define CAN2_TRX_STB_PORT       0
    #define CAN2_TRX_STB_PIN        0
    #define CAN2_TRX_STB_LVL        0   /* Choose High or Low active state for CAN Transceiver standby pin. */

    /* Configure CAN2 EN GPIO output pin. */
    #define CAN2_TRX_ENABLE_PORT    0
    #define CAN2_TRX_ENABLE_PIN     0
    #define CAN2_TRX_ENABLE_LVL     0   /* Choose High or Low active state for CAN Transceiver standby pin. */
#endif


/* CANレジスタビットを期待される値にポーリングする最大ループ数。ポーリングモードを使用している場合、
 * メールボックスがフレームを受信したことを確認するために一定時間待機したい場合は、この値を増やしてください。
 * この値は非常に低く設定できますが、ゼロに設定しないでください。そうしないと、メールボックスが全くチェックされない可能性があります！
 */
#define MAX_CANREG_POLLCYCLES   (5)

#endif    /* CAN_CONFIG_HEADER_FILE */
/* eof */
