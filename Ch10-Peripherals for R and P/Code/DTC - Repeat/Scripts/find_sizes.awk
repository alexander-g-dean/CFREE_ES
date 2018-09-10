# Find sizes of ROM items (functions and const data)
BEGIN { 
    	on = 0; done = 0;
    	num_regions = 0;
	adx_1 = 0;
	adx_2 = 0;

	in_code_segment = 0;
}

$0 == "MODULE MAP" {
    if (!done) 
		on = 1; 
	print 
}

NF == 1 && $1 !~ /R?CODE/ {
	in_code_segment = 0;
	step = 0;
}

NF == 1 && $1 ~ /^R?CODE/ { 
	in_code_segment = 1;
	step = 1;
}

NF == 1 && $1 ~ /^NEAR_CONST/ { 
	in_code_segment = 1;
	step = 1;
}

$1 == "Relative" && $2 == "segment," {
	if (in_code_segment==1) {
		adx_1 = $4;
		adx_2 = $6;
		len = strtonum(substr($7, 2));
		step = 2;
	}	
}

$1 == "ENTRY" && $2 == "ADDRESS" && $3 == "REF" && $4 == "BY" {
	if (step == 2) {
		step = 3;
	} else {
		step = 0;
	}
}

NF >= 2 && step == 4 {
	data[$1] = len;
	printf("%d \t%s\n", len, $1);
	step = 0;
}

$1 == "=====" && $2 == "=======" && $3 == "======" {
	if (step == 3) {
		step = 4;
	} else {
		step = 0;
	}
}



END {
}
