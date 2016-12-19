#!/usr/bin/perl

@array1=(1..12);
@array2=qw(2 4 6 8 10 12);
foreach $tmp(@array1){
if (!grep(/\b$tmp\b/,@array2)){
push @array3,"$tmp\n";
}
}
print @array3;
