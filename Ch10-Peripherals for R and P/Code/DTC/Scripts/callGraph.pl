#!/usr/bin/env perl

use warnings;
use strict;

if (@ARGV != 1) {
    die "usage: $0 <linker-map-filename>\n";
}

local $/ = "    -------------------------------------------------------------------------\r\n";
my $filename = $ARGV[0];
open FILE, "<$filename" or die $!;
my @records = <FILE>;
my @functionList;
close FILE;

_print_pre_graph();
_print_graph();
_print_post_graph();

sub _print_pre_graph
{
    print "<!DOCTYPE html>\n";
    print "<html lang=\"en\">\n";
    print "<head>\n";
    print "<meta charset=\"utf-8\"/>\n";
    print "<link href=\"callgraph.css\" rel=\"stylesheet\"/>";
}

sub _print_graph
{
    print "<script type=\"text/javascript\">\n";
    print "var graphEdges = [\n";
	
	foreach my $record (@records) {
		_process_record($record);
	}

    print "]\n";
    print "</script>\n";
}

sub _print_post_graph
{
    print "<script src=\"viz.js\"></script>\n";
    print "<script src=\"callgraph.js\"></script>\n";
    print "</head>\n";
    print "<body>\n";
    print '<div id="search"><form name="codeQuery" action="javascript:queryGraph();">' . "\n";
    print '<input name="callee" type="text" list="functionlist" onchange="" />' . "\n";
    print '<input name="submit" type="submit" value="Search" /></form></div>' . "\n";
    print '<datalist id="functionlist">' . "\n";
    print "\n";
    foreach my $func (@functionList) {
        print '<option value="' . $func . '" />' . "\n";
    }
    print '</datalist>' . "\n";
    print '<div id="callgraph"></div>' . "\n";
    print "</body>\n";
    print "</html>\n";
}

sub _process_record
{
	my ($record) = @_;
	my @sub_records = split(/\s{4}\*{73}/, $record);
	my $segment_location;
	my @record_parts;
	
	foreach my $sub_record (@sub_records) {
		$segment_location = index($sub_record, "Relative segment");
		if ($segment_location == -1) {
			next;
		}
		
		$sub_record = substr($sub_record, $segment_location);
		@record_parts = split(
				"           ENTRY                   ADDRESS         REF BY\r\n" .
				"           =====                   =======         ======\r\n",
				$sub_record);
		
		#Skip this sub_record if there's no entry name
		if (($#record_parts + 1) != 2) {
			next;
		}
		
		_print_refs($record_parts[0], $record_parts[1]);
	}
}

sub _print_refs
{
	my ($segment_info, $entry_info) = @_;
	
	my @intra_module_refs = _get_intra_module_refs($segment_info);
	
	my $local_idx = index($entry_info,
					   "           LOCAL                   ADDRESS         ");
	
	#Ignore local info, if present
	if ($local_idx != -1) {
		$entry_info = substr($entry_info, 0, $local_idx);
	}
	
	my $entry_name;
	($entry_name) = $entry_info =~ /^\s{11}(\S+)\s+[0-9A-F]+.*$/m;
	unless ($entry_name) {
		return;
	}
	
	push(@functionList, $entry_name);
	
	my @entries = split("\r\n", $entry_info);
	foreach my $entry_ref (@entries) {
		($entry_ref) = $entry_ref =~ m/^.{43}\s{8}(\S+)\s\(.*\)$/m;
		if ($entry_ref) {
			_print_ref($entry_ref, $entry_name);
		}
	}
	
	foreach my $module_ref (@intra_module_refs) {
		_print_ref($module_ref, $entry_name);
	}
}

sub _get_intra_module_refs
{
	my ($segment_info) = @_;
	my @refs = ();
	
	my $intra_module_idx = index($segment_info, "Intra module refs:");
	if ($intra_module_idx == -1) {
		return @refs;
	}
	
	#Remove heading
	$segment_info = substr($segment_info, $intra_module_idx + 21);
	
	@refs = split(/\r\n\s+/, $segment_info);
	foreach my $ref (@refs) {
		$ref = trim($ref);
	}
	
	return @refs;
}

sub _print_ref
{
	my ($caller, $callee) = @_;
	print "{\"called_by\":\"$caller\",\"functionName\":\"$callee\"},\n";
}

sub trim
{
	my $string = shift;
	$string =~ s/^\s+//;
	$string =~ s/\s+$//;
	return $string;
}

1;
