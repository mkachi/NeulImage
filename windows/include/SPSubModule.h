#pragma once

#ifdef SP_SM_EXPORTS
#define SP_SM __declspec(dllexport)
#else
#define SP_SM
#endif