# mrt: make region tables for profiling

BEGIN { 
    on = 0; done = 0;
    num_regions = 0;
	adx_1 = 0;
	adx_2 = 0;

	in_code_segment = 0;
    print "// Automatically generated file. Do not edit if you plan to regenerate it.\n"
    print "#include \"region.h\"";
    print "const REGION_T RegionTable[] = {";
}

$0 == "MODULE MAP" {
    if (!done) 
		on = 1; 
	print 
}

NF == 1 && $1 ~ /^R?CODE/ { 
	in_code_segment = 1;
	step = 1;
}

NF == 1 && $1 !~ /R?CODE/ {
	in_code_segment = 0;
	step = 0;
}

$1 == "Relative" && $2 == "segment," {
	if (in_code_segment==1) {
		adx_1 = $4;
		adx_2 = $6;
		step = 2;
	} else {
		adx_1 = 0;
		adx_2 = 0;
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
    num_regions++;
    printf("\t{0x%s, 0x%s, \"%1.15s\"}, \t\t//%d\n", adx_1, adx_2, $1,num_regions-1);
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
    print "};\n";
    printf("const unsigned NumProfileRegions=%d;\n", num_regions);
    printf("volatile unsigned RegionCount[%d];\n", num_regions);
}
