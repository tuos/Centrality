#!/usr/local/bin/perl


$f1 = 'dir.list';

for ($i=0;$i<20;$i++) {

  system("mkdir jb$i");

  $newline = 'jb'.$i."\n";
  push(@filelist, $newline);
}


open (DIRLIST, ">$f1") or die "Cannot open $integral for writing \n";
print DIRLIST @filelist;
close DIRLIST;
