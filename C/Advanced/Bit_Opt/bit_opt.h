#include <stdio.h>
#include <stdlib.h>

/*  
 * 假设ABCD三种灯对应的CAN信号值类似，只是值的含义不同。
 * 其中，ACD含义相同，B在ON/Flash的值不同。
 */

#define LAMP_IND_ON                 (1u)    /* Telltale Indication ON */
#define LAMP_IND_OFF                (0u)    /* Telltale Indication OFF */

#define LAMP_BLINK                  (1u)    /* Telltale Blink ON */
#define LAMP_NOBLINK              (0u)    /* Telltale Blink OFF */

/*
*           Offset of       Offset of
*           TT Status       TT Blink
*          |_______________|_______________
*  16 bits |_______________|_______________|    TT_LIST
*           0 1 1 0 ...     0 1 0 0 ...
*/
#define OFFSET_INDCT                (0u)
#define OFFSET_BLINK                (8u)

#define BIT_IND_0                   (OFFSET_INDCT + 0u)
#define BIT_IND_1                   (OFFSET_INDCT + 1u)
#define BIT_IND_2                   (OFFSET_INDCT + 2u)
#define BIT_IND_3                   (OFFSET_INDCT + 3u)

#define BIT_BLK_0                   (OFFSET_BLINK + 0u)
#define BIT_BLK_1                   (OFFSET_BLINK + 1u)
#define BIT_BLK_2                   (OFFSET_BLINK + 2u)
#define BIT_BLK_3                   (OFFSET_BLINK + 3u)
#define MAX_MSG_BIT                 (4u)

/*
[A]
CanValue |  TT Status
---------|-------------
  0x0u   |   TT Off
  0x1u   |   TT Flash
  0x2u   |   TT On
  0x3u   |   TT Off (Reserved)
*/
#define A_CAN_TT_LIST             (uint16)(((uint16)LAMP_IND_OFF << BIT_IND_0)\
                                           | ((uint16)LAMP_IND_ON  << BIT_IND_1)\
                                           | ((uint16)LAMP_IND_ON  << BIT_IND_2)\
                                           | ((uint16)LAMP_IND_OFF << BIT_IND_3)\
                                           | ((uint16)LAMP_NOBLINK << BIT_BLK_0)\
                                           | ((uint16)LAMP_BLINK   << BIT_BLK_1)\
                                           | ((uint16)LAMP_NOBLINK << BIT_BLK_2)\
                                           | ((uint16)LAMP_NOBLINK << BIT_BLK_3))

/*
[B]
CanValue |  TT Status
---------|-------------
  0x0u   |   TT Off
  0x1u   |   TT On
  0x2u   |   TT Flash
  0x3u   |   TT Off (Reserved)
*/
#define B_CAN_TT_LIST             (uint16)(((uint16)LAMP_IND_OFF << BIT_IND_0)\
                                           | ((uint16)LAMP_IND_ON  << BIT_IND_1)\
                                           | ((uint16)LAMP_IND_ON  << BIT_IND_2)\
                                           | ((uint16)LAMP_IND_OFF << BIT_IND_3)\
                                           | ((uint16)LAMP_NOBLINK << BIT_BLK_0)\
                                           | ((uint16)LAMP_NOBLINK << BIT_BLK_1)\
                                           | ((uint16)LAMP_BLINK   << BIT_BLK_2)\
                                           | ((uint16)LAMP_NOBLINK << BIT_BLK_3))

/*
[C]
CanValue |  TT Status
---------|-------------
  0x0u   |   TT Off
  0x1u   |   TT Flash
  0x2u   |   TT On
  0x3u   |   TT Off (Reserved)
*/
#define C_CAN_TT_LIST              A_CAN_TT_LIST

/*
[D]
CanValue |  TT Status
---------|-------------
  0x0u   |   TT Off
  0x1u   |   TT Flash
  0x2u   |   TT On
  0x3u   |   TT Off (Reserved)
*/
#define D_CAN_TT_LIST             A_CAN_TT_LIST


typedef enum {
    LAMP_A = 0u,
    LAMP_B,
    LAMP_C,
    LAMP_D,
    LAMP_MAX_CNT
} eLamp_Index;

typedef signed char           sint8;
typedef unsigned char         uint8;
typedef signed short          sint16;
typedef unsigned short        uint16;
typedef signed long           sint32;
typedef unsigned long         uint32;


/**************************************************/

#define TEST_LEN        (4u)
