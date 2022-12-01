#ifndef __FETCH_INSERT_H__
#define __FETCH_INSERT_H__

#define USE_IDOL_OEM_ENCRYPTION 1
#define IDOL_OEM_ENCRYPTION_KEY_ENV_VAR "ACI_API_TUTORIAL_PROGRAM_ENCRYPTION_KEY"
#define IDOL_OEM_ENCRYPTION_KEY_STUB_VALUE "REPLACE_WITH_MY_LONG_KEY_STRING"
/* When enabling OEM encryption, replace the following value with issued key */
#define IDOL_OEM_ENCRYPTION_KEY IDOL_OEM_ENCRYPTION_KEY_STUB_VALUE

#define EXPECTED_NUM_ARGS (3+2)

#define MAX_INSERT_XML_SIZE_BYTES 10000

char* get_insertXML_file(const char* path, size_t* f_size);

#endif  /*__FETCH_INSERT_H__*/
