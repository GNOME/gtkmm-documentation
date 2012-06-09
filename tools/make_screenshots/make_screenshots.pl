#!/usr/bin/perl

# Generate screenshots for the gtkmm tutorial.
#
# This Perl script starts one or more programs, one at a time. The started
# programs are assumed to open a window. The script catches a screenshot of
# each started program's window.
# The script can't correctly generate screenshots that require some kind of
# user input before or after the program has been started.
#
# Which programs to start and where to save the screenshots is read from a
# file, where each line contains
#   program [parameter-to-program...] figure [delay-in-seconds] [# comment]
# Lines that don't contain both 'program' and 'figure' are ignored.

# The screenshots are saved by gnome-screenshot.
# The gnome-screenshot bugs https://bugzilla.gnome.org/show_bug.cgi?id=129768 and
# https://bugzilla.gnome.org/show_bug.cgi?id=594141 must have been implemented.

use strict;
use warnings;

use Getopt::Long qw(:config no_ignore_case);
use POSIX qw(:sys_wait_h); # waitpid
use File::Basename;

my $help = 0;
my $program_prefix = "";
my $figure_prefix = "";

my $optResult = GetOptions(
  'help' => \$help,
  'program-prefix=s' => \$program_prefix,
  'figure-prefix=s'=> \$figure_prefix);

if (!$optResult or $help or @ARGV != 1)
{
  my $prog_name = basename($0);
  print "$prog_name [--program-prefix=program-prefix] [--figure-prefix=figure-prefix] listfile\n";
  print "Format of each line in listfile:\n";
  print "  program [parameter-to-program...] figure [delay-in-seconds] [# comment]\n";
  exit !$optResult;
}

open(LISTFILE, $ARGV[0]) or die "Can't open $ARGV[0]: $!\n";

while (defined(my $line = <LISTFILE>))
{
  chomp $line;

  # Remove comments.
  $line =~ s/#.*//;

  my @fields = split ' ',  $line;

  # Skip lines with less than two fields.
  # These are blank lines, comment lines, and lines with the name of a program
  # from which no screenshot is required.
  next if @fields < 2;

  my $delay = 2;
  if (@fields >= 3 and $fields[-1] =~ /^\d+$/)
  {
    # The last field consists of only digits. It's the required delay.
    $delay = pop(@fields);
  }

  my $program = $program_prefix . $fields[0];
  my ($program_filename, $program_directory, $dummy_suffix) = fileparse($program);

  my $figure = $figure_prefix . $fields[-1];
  my @cmd_par = ();
  if (@fields > 2)
  {
    @cmd_par = @fields[1 .. $#fields-1];
  }

  defined(my $pid = fork) or die "Can't fork: $!\n";
  if (!$pid)
  {
    # Child process.
    # Execute the program in its own directory.
    # Some programs will find necessary data files only if they are executed in
    # their own directory.
    chdir $program_directory or die "Can't chdir to $program_directory: $!\n";
    exec "./$program_filename", @cmd_par;
    die "Can't exec $program: $!\n";
  }

  # Parent process.
  # Wait for the child process to show its main window.
  sleep $delay;

  # Reap the child process, if it has become a zombie.
  waitpid $pid, WNOHANG;
  # Check if the child process still exists.
  die "Could not start program from line: $line\n" if kill(0, $pid) == 0;

  my $result = system("gnome-screenshot --window --file=$figure");
  kill 9, $pid;
  die "Can't save screenshot from line: $line\n" if $result != 0;
}
close LISTFILE;
exit 0;

