 #!/usr/local/bin/perl

$debug=1;

# open file as read_only
$dirlist ="dir.list";
open(DIRLIST,"< $dirlist") or die "Can not open ${filelist} !\n";

#$filelist ="file.list";
$filelist ="filelistAll.txt";
open(FILELIST,"< $filelist") or die "Can not open ${filelist} !\n";

my @filelines = <FILELIST>;

$nfiles=0;

$j=0;

while (<DIRLIST>) {
    $dir = $_;
    chomp($dir);
#    printf("dir=%s\n", $dir);
    $back = "..";

    $first = 0;
    $last = $nfiles;
    
#    system("cp lyzerosanaptdz08fp_cfg.py $dir");
     
    chdir $dir;  
 

    $filename = "filelist.txt";
    open(FILENAME,">$filename");

    foreach my $line ($j..$j+$nfiles)
    {
 #       print "$filelines[$line]"; 
#        print FILENAME '/pnfs/cmsaf.mit.edu/t2bat/cms';
	print FILENAME $filelines[$line];
	$j=$j+1;
    }
 
    $first=$first+$j;
    $last=$first+$nfiles;
#    printf "$first  $last\n";

    chdir $back;


}

# to close the file handles
close DIRLIST;
close FILELIST;
close FILENAME;
