#include <atf-c.h>
#include "libconf.h"

#define STR_SIZE(x) (x),(sizeof(x)-1)

void tc0_parser(struct conf_state *cst, void *arg)
{
	char argbuf[10];
	conf_string(cst, argbuf, sizeof(argbuf));
	ATF_CHECK_EQ(strcmp(argbuf, "foo"), 0);
}

ATF_TC_WITHOUT_HEAD(tc0);
ATF_TC_BODY(tc0, tc)
{
	struct conf_state cst;
	conf_parse(&cst, tc0_parser, fmemopen(STR_SIZE("foo"), "r"), NULL);
}

void tc4_parser(struct conf_state *cst, void *arg)
{
	char buf[10];	
	ATF_CHECK_EQ(conf_string(cst, buf, sizeof(buf)), 9);
}

ATF_TC_WITHOUT_HEAD(tc4);
ATF_TC_BODY(tc4, tc)
{
	struct conf_state cst;
	conf_parse(&cst, tc4_parser, fmemopen(STR_SIZE("01234567890"), "r"), NULL);
}

ATF_TP_ADD_TCS(tp)
{
	ATF_TP_ADD_TC(tp, tc0);
	ATF_TP_ADD_TC(tp, tc4);
	return atf_no_error();
}
