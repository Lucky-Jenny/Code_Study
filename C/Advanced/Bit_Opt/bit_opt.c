/**
 * @file          bit_opt.c
 * @author        Liu, Xiao
 * @brief         In common codes, when values range from 0-1,
 *                we can dealthem by bit instead of values.
 */

#include "bit_opt.h"

/*  << data declaration area for globals >>  */
static uint16 Can_list_arry[LAMP_MAX_CNT] = {A_CAN_TT_LIST,
                                             B_CAN_TT_LIST,
                                             C_CAN_TT_LIST,
                                             D_CAN_TT_LIST};
static uint8 LampIndct_Sts[LAMP_MAX_CNT];
static uint8 LampBlink_Sts[LAMP_MAX_CNT];

static sint8 test_input[TEST_LEN][2] = {{LAMP_A, 2},
                                        {LAMP_D, 0},
                                        {LAMP_C, 5},
                                        {LAMP_D, 1}};
/*  << function declaration area >>  */
static void Config_Lamp_from_CAN_Values(eLamp_Index idx, uint8 canValue);
static void Show_Lamp_Status(void);

/*  << function definition area >>  */

int main()
{
    for(uint8 i = 0u; i < TEST_LEN; i++){
        Config_Lamp_from_CAN_Values(test_input[i][0], test_input[i][1]);
        Show_Lamp_Status();
    }
}

static void Config_Lamp_from_CAN_Values(eLamp_Index idx, uint8 canValue)
{
    if(canValue < MAX_MSG_BIT){
        LampIndct_Sts[idx] = (uint8)((uint16)0x1u & (Can_list_arry[idx] >> (OFFSET_INDCT + canValue)));
        LampBlink_Sts[idx] = (uint8)((uint16)0x1u & (Can_list_arry[idx] >> (OFFSET_BLINK + canValue)));
        printf("Can %c = %d  \t--> ", 'A'+idx, canValue);
    }else{
        printf("Value Invalid\t--> ");
    }
}

static void Show_Lamp_Status(void)
{
    char x = 'A';

    for(int i = 0; i < LAMP_MAX_CNT; i++){
        x = 'A' + i;
        if(LampIndct_Sts[i] == LAMP_IND_OFF){
            printf("Lamp %c: OFF\t", x);
        }else{
            if(LampBlink_Sts[i] == LAMP_BLINK){
                printf("Lamp %c: Blink\t", x);
            }else{
                printf("Lamp %c: ON\t", x);
            }
        }
    }
	printf("\n");
}
