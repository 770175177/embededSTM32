#include "adxl345.h"
#include "usart.h"
#include "log_module.h"

int8_t adxl345_init()
{
	uint8_t devid = 0;

	spi1_init();

	if (ADXL345_DEVICEID != (devid = adxl345_read(ADXL_DEVICEID))) {
		ADXL345_PRINT("Read ADXL345 device id 0x%x error!\r\n", devid);
		return -1;
	}

	adxl345_write(ADXL_DAT_FORMAT, 0x0B);		// 13-bits data, 16g
	adxl345_write(ADXL_PWR_CTRL, 0x08);			// measure
	adxl345_write(ADXL_BW_RATE, 0x0F);			// 100Hz
	adxl345_write(ADXL_INT_ENABLE, 0x00);		// data ready interrupt

	adxl345_write(ADXL_OFFSX, 2);
	adxl345_write(ADXL_OFFSY, 10);
	adxl345_write(ADXL_OFFSZ, -20);

	ADXL345_PRINT("ADXL345 init success, device id is 0x%x\r\n", devid);

	return 0;
}

int8_t adxl345_write_read_bytes(u8 txrx_data[], uint8_t length)
{
	uint8_t recv_data = 0, i = 0;
	int8_t	ret = 0;

	for (i = 0; i < length; i++) {
		if (ret = spi1_write_read_byte(txrx_data[i], &recv_data)) {
			ADXL345_PRINT("Write(-1) or Read(-2) data error, ret %d\r\n", ret);
			return -1;
		}
		if (0 != i)
			txrx_data[i] = recv_data;
	}

	return 0;
}

void adxl345_write(uint8_t addr, uint8_t value)
{
	uint8_t txrx[2];

	spi1_nss_set(LOW);
	txrx[0] = addr & 0x3F;
	txrx[1] = value;

	adxl345_write_read_bytes(txrx, 2);
	spi1_nss_set(HIGH);
}

uint8_t adxl345_read(uint8_t addr)
{
	uint8_t txrx[2];

	spi1_nss_set(LOW);
	txrx[0] = addr & 0x3F;
	txrx[0] |= 0x80;
	txrx[1] = 0xFF;

	adxl345_write_read_bytes(txrx, 2);
	spi1_nss_set(HIGH);

	return txrx[1];
}

uint16_t adxl345_read_burst(uint8_t addr)
{
	uint8_t txrx[3];

	spi1_nss_set(LOW);
	txrx[0] = addr & 0x3F;
	txrx[0] |= 0xC0;
	txrx[1] = 0xFF;
	txrx[2] = 0xFF;

	adxl345_write_read_bytes(txrx, 3);
	spi1_nss_set(HIGH);

	return *((uint16_t *)&txrx[1]);
}

void adxl345_read_xyz_axis(uint16_t *xAxis, uint16_t *yAxis, uint16_t *zAxis)
{
	*xAxis = adxl345_read_burst(ADXL_DAT_X0);
	*yAxis = adxl345_read_burst(ADXL_DAT_Y0);
	*zAxis = adxl345_read_burst(ADXL_DAT_Z0);
}

void adxl345_read_x_axis(uint16_t *xAxis)
{
	*xAxis = adxl345_read_burst(ADXL_DAT_X0);
}

void adxl345_read_y_axis(uint16_t *yAxis)
{
	*yAxis = adxl345_read_burst(ADXL_DAT_Y0);
}

void adxl345_read_z_axis(uint16_t *zAxis)
{
	*zAxis = adxl345_read_burst(ADXL_DAT_Z0);
}





























