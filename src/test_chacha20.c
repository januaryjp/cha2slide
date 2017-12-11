#include "test_chacha20.h"

#define check_states(a, b) for (int i = 0; i < 16; i++) if (a[i] != b[i]) goto failed;


MunitResult test_chacha20_quarter_round(const MunitParameter params[], void* user_data)
{
	uint32_t expected[16] = {0x879531e0, 0xc5ecf37d, 0xbdb886dc, 0xc9a62f8a, 0x44c20ef3, 0x3390af7f, 0xd9fc690b, 0xcfacafd2, 0xe46bea80, 0xb00a5631, 0x974c541a, 0x359e9963, 0x5c971061, 0xccc07c79, 0x2098d9d6, 0x91dbd320};
	uint32_t state[16] = {0x879531e0, 0xc5ecf37d, 0x516461b1, 0xc9a62f8a, 0x44c20ef3, 0x3390af7f, 0xd9fc690b, 0x2a5f714c, 0x53372767, 0xb00a5631, 0x974c541a, 0x359e9963, 0x5c971061, 0x3d631689, 0x2098d9d6, 0x91dbd320};
	
	chacha20_quarter_round(state, 2,7,8,13);
	
	check_states(expected, state);
	return MUNIT_OK;
failed:
	return MUNIT_FAIL;
}

MunitResult test_chacha20_setup(const MunitParameter params[], void* user_data)
{
	uint32_t expected[16] = {0x61707865, 0x3320646e, 0x79622d32, 0x6b206574, 0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c, 0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c, 0x00000001, 0x09000000, 0x4a000000, 0x00000000};
	const unsigned char key[32] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};
	const unsigned char nonce[12] = {0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x4a, 0x00, 0x00, 0x00, 0x00};
	uint32_t state[16] = {0};
	
	chacha20_setup(state, key, nonce, 1);
	
	check_states(expected, state);
	return MUNIT_OK;
failed:
	return MUNIT_FAIL;
}

MunitResult test_chacha20_block(const MunitParameter params[], void* user_data)
{
	uint32_t expected[16] = {0xe4e7f110, 0x15593bd1, 0x1fdd0f50, 0xc47120a3, 0xc7f4d1c7, 0x0368c033, 0x9aaa2204, 0x4e6cd4c3, 0x466482d2, 0x09aa9f07, 0x05d7c214, 0xa2028bd9, 0xd19c12b5, 0xb94e16de, 0xe883d0cb, 0x4e3c50a2};
	const unsigned char key[32] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};
	const unsigned char nonce[12] = {0x00, 0x00, 0x00, 0x09, 0x00, 0x00, 0x00, 0x4a, 0x00, 0x00, 0x00, 0x00};
	uint32_t state[16] = {0};
	
	chacha20_setup(state, key, nonce, 1);
	chacha20_block(state);
	
	check_states(expected, state);
	return MUNIT_OK;
failed:
	return MUNIT_FAIL;
}

MunitResult test_chacha20_stream(const MunitParameter params[], void* user_data)
{
	const unsigned char key[32] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};
	const unsigned char nonce[12] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4a, 0x00, 0x00, 0x00, 0x00};
	uint32_t expected_setup_state_1[16] = {0x61707865, 0x3320646e, 0x79622d32, 0x6b206574, 0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c, 0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c, 0x00000001, 0x00000000, 0x4a000000, 0x00000000};
	uint32_t expected_setup_state_2[16] = {0x61707865, 0x3320646e, 0x79622d32, 0x6b206574, 0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c, 0x13121110, 0x17161514, 0x1b1a1918, 0x1f1e1d1c, 0x00000002, 0x00000000, 0x4a000000, 0x00000000};
	uint32_t expected_state_1[16] = {0xf3514f22, 0xe1d91b40, 0x6f27de2f, 0xed1d63b8, 0x821f138c, 0xe2062c3d, 0xecca4f7e, 0x78cff39e, 0xa30a3b8a, 0x920a6072, 0xcd7479b5, 0x34932bed, 0x40ba4c79, 0xcd343ec6, 0x4c2c21ea, 0xb7417df0};
	uint32_t expected_state_2[16] = {0x9f74a669, 0x410f633f, 0x28feca22, 0x7ec44dec, 0x6d34d426, 0x738cb970, 0x3ac5e9f3, 0x45590cc4, 0xda6e8b39, 0x892c831a, 0xcdea67c1, 0x2b7e1d90, 0x037463f3, 0xa11a2073, 0xe8bcfb88, 0xedc49139};
	uint32_t setup_state_1[16] = {0};
	uint32_t setup_state_2[16] = {0};
	uint32_t state_1[16] = {0};
	uint32_t state_2[16] = {0};

	chacha20_setup(setup_state_1, key, nonce, 1);
	check_states(expected_setup_state_1, setup_state_1);
	
	chacha20_setup(setup_state_2, key, nonce, 2);
	check_states(expected_setup_state_2, setup_state_2);
	
	memcpy(state_1, setup_state_1, 64);
	chacha20_block(state_1);
	check_states(expected_state_1, state_1);
	
	memcpy(state_2, setup_state_2, 64);
	chacha20_block(state_2);
	check_states(expected_state_2, state_2);
	
	return MUNIT_OK;
failed:
	return MUNIT_FAIL;
}

MunitResult test_chacha20_encrypt(const MunitParameter params[], void* user_data)
{
	unsigned char expected[] = {0x6e, 0x2e, 0x35, 0x9a, 0x25, 0x68, 0xf9, 0x80, 0x41, 0xba, 0x07, 0x28, 0xdd, 0x0d, 0x69, 0x81, 0xe9, 0x7e, 0x7a, 0xec, 0x1d, 0x43, 0x60, 0xc2, 0x0a, 0x27, 0xaf, 0xcc, 0xfd, 0x9f, 0xae, 0x0b, 0xf9, 0x1b, 0x65, 0xc5, 0x52, 0x47, 0x33, 0xab, 0x8f, 0x59, 0x3d, 0xab, 0xcd, 0x62, 0xb3, 0x57, 0x16, 0x39, 0xd6, 0x24, 0xe6, 0x51, 0x52, 0xab, 0x8f, 0x53, 0x0c, 0x35, 0x9f, 0x08, 0x61, 0xd8, 0x07, 0xca, 0x0d, 0xbf, 0x50, 0x0d, 0x6a, 0x61, 0x56, 0xa3, 0x8e, 0x08, 0x8a, 0x22, 0xb6, 0x5e, 0x52, 0xbc, 0x51, 0x4d, 0x16, 0xcc, 0xf8, 0x06, 0x81, 0x8c, 0xe9, 0x1a, 0xb7, 0x79, 0x37, 0x36, 0x5a, 0xf9, 0x0b, 0xbf, 0x74, 0xa3, 0x5b, 0xe6, 0xb4, 0x0b, 0x8e, 0xed, 0xf2, 0x78, 0x5e, 0x42, 0x87, 0x4d};
	const unsigned char key[32] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f};
	const unsigned char nonce[12] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4a, 0x00, 0x00, 0x00, 0x00};
	char *stack = "Ladies and Gentlemen of the class of '99: If I could offer you only one tip for the future, sunscreen would be it.";
	uint32_t length = strlen(stack);
	char *string = malloc(length);
	memcpy(string, stack, length);
	
	chacha20(key, nonce, (uint8_t*)string, length, 1);
	for (uint32_t i = 0; i < length; i++) if (((unsigned char*)string)[i] != expected[i]) goto failed;
	
	free(string);
	return MUNIT_OK;
failed:
	free(string);
	return MUNIT_FAIL;
}
