#include "FileUtil.h"

#include <stdio.h>
#define _STDC_FORMAT_MACROS
#include <inttypes.h> // fixed size integer types

int main()
{
	string result;
	int64_t size = 0;
	int err = FileUtil::readFile("/proc/self", 1024, &result, &size);
	printf("%d %zd %" PRIu64 "\n", err, result.size(), size);

	return 0;
}
