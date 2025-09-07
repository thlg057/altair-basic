#ifndef PROGRAM_H
#define PROGRAM_H

#include "error.h"

ResultCode clearProgram(void);
ResultCode addLine(const char *line);
ResultCode runProgram(void);
ResultCode listProgram(void);

#endif
