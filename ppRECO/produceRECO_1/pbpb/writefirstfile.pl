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
    system("cp step2_RAW2DIGI_L1Reco_RECO.py $newfile");
    system("sed 's/jb0/jb$nn/g' $newfile/step2_RAW2DIGI_L1Reco_RECO.py > $newfile/temp.py");
    system("mv $newfile/temp.py $newfile/step2_RAW2DIGI_L1Reco_RECO.py");

    system("cp submit.slurm $newfile");
    system("sed 's/jb0/jb$nn/g' $newfile/submit.slurm > $newfile/temp.py");
    system("mv $newfile/temp.py $newfile/submitjob$nn.slurm");
    system("rm -f $newfile/submit.slurm");
#
   $i=$i+$nfiles;
}

# to close the file handles
close LIST;
