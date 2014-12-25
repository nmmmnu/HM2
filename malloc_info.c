#include <malloc.h>
#include <stdio.h>


inline static void myprintf(const char *d1, const char *d2, const int val){
	const char *format = "%-30s %-10s = %15d\n";

	printf(format, d1, d2, val);
}


void display_mallinfo(int fullinfo){
	struct mallinfo m = mallinfo();

	printf("Malloc information:\n");

	if (fullinfo){
		myprintf("Total non-mmapped bytes"	,	"arena"		,	m.arena		);
		myprintf("# of free chunks" 		,	"ordblks"	,	m.ordblks	);
		myprintf("# of free fastbin blocks"	,	"smblks"	,	m.smblks	);
		myprintf("# of mapped regions"		,	"hblks"		,	m.hblks		);
		myprintf("Bytes in mapped regions"	,	"hblkhd"	,	m.hblkhd	);
		myprintf("Max. total allocated space"	,	"usmblks"	,	m.usmblks	);
		myprintf("Free bytes held in fastbins"	,	"fsmblks"	,	m.fsmblks	);
		myprintf("Total allocated space"	,	"uordblks"	,	m.uordblks	);
		myprintf("Total free space"		,	"fordblks"	,	m.fordblks	);
		myprintf("Topmost releasable block"	,	"keepcost"	,	m.keepcost	);
	}else{
		myprintf("Total non-mmapped bytes"	,	"arena"		,	m.arena		);
		myprintf("Bytes in mapped regions"	,	"hblkhd"	,	m.hblkhd	);
	}
}

