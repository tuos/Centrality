 #!/usr/local/bin/perl


$debug=1;

# open file as read_only
$filelist ="dir.list";
open(LIST,"< $filelist") or die "Can not open ${filelist} !\n";

$i=1;
$nfiles=1;
while (<LIST>) {
    $nn=($i-1)/1;
#    $nnn=$i/100;
    $onefile = $_;
    chomp($onefile);
#    if ($nnn == 0)
#    printf("file=%s  \n", $onefile);
    $newfile="$onefile";
    #system("cd $newfile\n");
    system("cp get_FilteredEvents.py $newfile");
    system("sed 's/jb0/jb$nn/g' $newfile/get_FilteredEvents.py > $newfile/temp.py");
    #system("sed 's/cent0/cent$nn/g' $newfile/temp.py > $newfile/tempy.py");
    ##system("sed 's/\\[0/[$nn/g' $newfile/temp.py > $newfile/tempz.py");
    system("mv $newfile/temp.py $newfile/get_FilteredEvents.py");
    ##system("rm -f $newfile/temp.py");
    #system("rm -f $newfile/tempy.py");

    system("cp submit.slurm $newfile");
    system("sed 's/jb0/jb$nn/g' $newfile/submit.slurm > $newfile/temp.slurm");
    system("mv $newfile/temp.slurm $newfile/submitjob$nn.slurm");
    system("rm -f $newfile/submit.slurm");
#
   $i=$i+$nfiles;
}

# to close the file handles
close LIST;
