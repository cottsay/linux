#include <linux/cdev.h>

#include <mach/power_gate.h>

#include <linux/amlogic/hdmi_tx/hdmi_tx_cec.h>

void cec_vendor_remote_btn_down_irq(void)
{
    unsigned char initiator = cec_global_info.cec_rx_msg_buf.cec_rx_message[cec_global_info.cec_rx_msg_buf.rx_write_pos].content.msg.header >> 4;

    if(initiator != 0xf)
    {
        switch(cec_global_info.cec_node_info[initiator].vendor_id) {
            case CEC_VENDOR_SAMSUNG:
                cec_user_control_pressed_irq();
                cec_user_control_released_irq(); // Samsung doesn't send a button-up
                break;
            case CEC_VENDOR_UNKNOWN:
            default:
                break;
        }
    }
}

void cec_vendor_remote_btn_up_irq(void)
{
    unsigned char initiator = cec_global_info.cec_rx_msg_buf.cec_rx_message[cec_global_info.cec_rx_msg_buf.rx_write_pos].content.msg.header >> 4;

    if(initiator != 0xf)
    {
        switch(cec_global_info.cec_node_info[initiator].vendor_id) {
            case CEC_VENDOR_SAMSUNG:
                cec_user_control_released_irq();
                break;
            case CEC_VENDOR_UNKNOWN:
            default:
                break;
        }
    }
}

