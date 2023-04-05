/*******************************************************************************
*
* FILE:
* 		main.c
*
* DESCRIPTION:
* 		Processes commands recieved from a host PC, provides fine control over
*       valve controller hardware resources
*
*******************************************************************************/


/*------------------------------------------------------------------------------
 Project Includes
------------------------------------------------------------------------------*/

/* Application Layer */
#include "sdr_pin_defines_L0005.h"
#include "main.h"
#include "init.h"

/* Module Layer */
#include "commands.h"
#include "led.h"
#include "solenoid.h"
#include "sensor.h"
#include "usb.h"
#include "valve.h"


/*------------------------------------------------------------------------------
 Global Variables
------------------------------------------------------------------------------*/
TIM_HandleTypeDef  htim2;  /* Fuel main valve control PWM signals */
TIM_HandleTypeDef  htim15; /* LOX main valve control PWM signals  */
UART_HandleTypeDef huart1; /* UART to USB                         */
UART_HandleTypeDef huart3; /* UART to engine controller           */


/*------------------------------------------------------------------------------
 Application entry point
------------------------------------------------------------------------------*/
int main
	(
	void
	)
{
/*------------------------------------------------------------------------------
 Local Variables
------------------------------------------------------------------------------*/
uint8_t       command;        /* SDEC command code          */
USB_STATUS    usb_status;     /* UART/USB status            */
VALVE_STATUS  valve_status;   /* Valve module return codes  */


/*------------------------------------------------------------------------------
 Initializations 
------------------------------------------------------------------------------*/
usb_status    = USB_OK;
valve_status  = VALVE_OK;


/*------------------------------------------------------------------------------
 MCU Initialization
------------------------------------------------------------------------------*/
HAL_Init           ();   /* CMSIS HAL               */
SystemClock_Config ();   /* System clock            */
GPIO_Init          ();   /* GPIO                    */
USB_UART_Init      ();   /* USB UART                */
Valve_UART_Init    ();   /* Engine Controller UART  */
LOX_Valve_TIM_Init ();   /* LOX Valve control timer */
Fuel_Valve_TIM_Init();   /* Fuel Valve control timer */


/*------------------------------------------------------------------------------
 External Hardware initializations 
------------------------------------------------------------------------------*/

/* Sensor module */
sensor_init();

/* Indicate successful initialization with green status LED */
led_set_color( LED_GREEN );

// Test
valve_enable_valves();
HAL_Delay( 5 );
valve_calibrate_valves();


/*------------------------------------------------------------------------------
 Event Loop
------------------------------------------------------------------------------*/
while (1)
	{
	if ( usb_detect() )
		{
		/* Read data from UART reciever */
		usb_status = usb_receive( &command         , 
		                          sizeof( command ), 
								  HAL_DEFAULT_TIMEOUT );

		/* Parse command input if HAL_UART_Receive doesn't timeout */
		if ( usb_status == USB_OK )
			{
			command_handler( command, CMD_SOURCE_USB );
			} 

		/* Poll data from valve control interface */
		/* 
		valve_status = valve_receive( &command         , 
		                              sizeof( command ),
									  HAL_DEFAULT_TIMEOUT );
									  */
		
		/* Execute command if valid */
		/*
		if ( valve_status == VALVE_OK )
			{
			command_handler( command, CMD_SOURCE_VALVE );
			}
			*/

		} /* if ( usb_detect() )*/
	}
} /* main */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
* 		command_handler                                                        *
*                                                                              *
* DESCRIPTION:                                                                 *
* 		Processes commands from the SDEC terminal                              *
*                                                                              *
*******************************************************************************/
void command_handler
	(
	uint8_t    command,     /* sdec command                              */
	CMD_SOURCE cmd_source   /* Determines which serial interface is used */
	)
{
/*------------------------------------------------------------------------------
 Local Variables
------------------------------------------------------------------------------*/
SENSOR_STATUS sensor_status;    /* Return codes from sensor API */
USB_STATUS    usb_status;       /* Return codes from USB API    */
VALVE_STATUS  valve_status;     /* Return codes from valve API  */
uint8_t       subcommand;       /* SDEC subcommands             */
uint8_t       firmware_code;    /* Firmware identifying code    */


/*------------------------------------------------------------------------------
 Initializations 
------------------------------------------------------------------------------*/
sensor_status = SENSOR_OK;
usb_status    = USB_OK;
valve_status  = VALVE_OK;
subcommand    = 0;
firmware_code = FIRMWARE_TERMINAL;


/*------------------------------------------------------------------------------
 Implementation 
------------------------------------------------------------------------------*/
switch( command )
	{
	/* Ping Command ----------------------------------------------------------*/
	case PING_OP:
		{
		ping( cmd_source );
		break;
		} /* PING_OP */

	/* Connect Command -------------------------------------------------------*/
	case CONNECT_OP:
		{
		/* Board identifier */
		ping( cmd_source );

		/* Firmware identifier */
		usb_transmit( &firmware_code, sizeof( uint8_t ), HAL_DEFAULT_TIMEOUT );
		break;
		} /* CONNECT_OP */

	/* Solenoid Command ------------------------------------------------------*/
	case SOL_OP:
		{
		/* Get subcommand */
		if ( cmd_source == CMD_SOURCE_USB )
			{
			usb_status = usb_receive( &subcommand, 
									sizeof( subcommand ), 
									HAL_DEFAULT_TIMEOUT );
			if ( usb_status == USB_OK )
				{
				solenoid_cmd_execute( subcommand );
				}
			else
				{
				/* Do nothing */
				Error_Handler();
				}
			}
		else
			{
			valve_status = valve_receive( &subcommand         , 
			                              sizeof( subcommand ), 
										  HAL_DEFAULT_TIMEOUT );
			if ( valve_status == VALVE_OK )
				{
				solenoid_cmd_execute( subcommand );
				}
			else
				{
				Error_Handler();
				}
			
			}
		break;
		} /* SOL_OP */

	/* Sensor Command --------------------------------------------------------*/
	case SENSOR_OP:
		{
		if ( cmd_source == CMD_SOURCE_USB )
			{
			usb_status = usb_receive( &subcommand, 
									sizeof( subcommand ),
									HAL_DEFAULT_TIMEOUT );
			if ( usb_status == USB_OK )
				{
				sensor_status = sensor_cmd_execute( subcommand, cmd_source );
				if ( sensor_status != SENSOR_OK )
					{
					Error_Handler();
					}
				}
			else
				{
				Error_Handler();
				}
			}
		else
			{
			valve_status = valve_receive( &subcommand         , 
			                              sizeof( subcommand ), 
										  HAL_DEFAULT_TIMEOUT );
			if ( valve_status == VALVE_OK )
				{
				sensor_status = sensor_cmd_execute( subcommand, cmd_source );
				if ( sensor_status != SENSOR_OK )
					{
					Error_Handler();
					}
				}
			else
				{
				Error_Handler();
				}
			}
		break;
		} /* SENSOR_OP */

	/* Valve command ---------------------------------------------------------*/
	case VALVE_OP:
		{
		if ( cmd_source == CMD_SOURCE_USB )
			{
			/* Get subcommand */
			usb_status = usb_receive( &subcommand         , 
									sizeof( subcommand ),
									HAL_DEFAULT_TIMEOUT );

			/* Execute subcommand */
			if ( usb_status != USB_OK )
				{
				Error_Handler();
				}
			else
				{
				valve_status = valve_cmd_execute( subcommand );
				if ( valve_status != VALVE_OK )
					{
					Error_Handler();
					}
				}
			}
		else
			{
			/* Get subcommand */
			valve_status = valve_receive( &subcommand         , 
			                              sizeof( subcommand ), 
										  HAL_DEFAULT_TIMEOUT );
			
			/* Execute subcommand */
			if ( valve_status != VALVE_OK )
				{
				Error_Handler();
				}
			else
				{
				valve_status = valve_cmd_execute( subcommand );
				if ( valve_status != VALVE_OK )
					{
					Error_Handler();
					}
				}
			}
		break;
		} /* VALVE_OP */

	/* Unrecognized Command -----------------------------------------*/
	default:
		{
		/* Unrecognized command code */
//		Error_Handler();
		break;
		}
	} /* switch( command ) */

} /* command handler */


/*******************************************************************************
*                                                                              *
* PROCEDURE:                                                                   *
* 		Error_Handler                                                          *
*                                                                              *
* DESCRIPTION:                                                                 *
* 		Handles software errors by turing the status LED red                   *
*                                                                              *
*******************************************************************************/
void Error_Handler(void)
{
  __disable_irq();
  led_error_assert();
  while (1)
	{
	/* Application hangs */
	}
} /* Error_Handler */


/*******************************************************************************
* END OF FILE                                                                  *
*******************************************************************************/