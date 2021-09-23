#! /usr/bin/perl -w

use strict;

#sub main()
{
  my $examples_base = shift(@ARGV);

  $examples_base .= "/" unless($examples_base =~ /\/$/);

  foreach my $file (@ARGV)
  {
    open(FILE, $file);

    while(<FILE>)
    {
      # Look for
      # <para><link xlink:href="&url_examples_base;helloworld">Source Code</link></para> [<!-- Insert filenames... -->]

      if(/<para><link xlink:href=\"&url_examples_base;([\/\w]+)\">Source Code<\/link><\/para>\s*(?:<!--\s*Insert\s+(.*?)-->)?/)
      {
        # Modify the line to remove the trailing comment, if any.
        # url_examples_base is assumed to be a GitLab URL. The branch is then
        # included in url_examples_base. No need to add it here.
        print "<para><link xlink:href=\"&url_examples_base;$1\">Source Code</link></para>\n";

        #List all the source files in that directory:
        my $directory = $examples_base . $1;

        #And possibly other files in that directory:
        my @extra_files;
        @extra_files = split ' ', $2 if defined($2);

        opendir(DIR, $directory);
        my @dir_contents = readdir(DIR);
        closedir(DIR);

        my @source_files = grep(/\.cc$/, @dir_contents);
        my @header_files = grep(/\.h$/,  @dir_contents);

        print "<!-- start inserted example code -->\n";

        foreach my $source_file (@header_files, @source_files)
        {
          &process_source_file($directory, $source_file, 1);
        }

        foreach my $source_file (@extra_files)
        {
          &process_source_file($directory, $source_file, 0);
        }

        print "<!-- end inserted example code -->\n";
      }
      else
      {
        # Just print the line without changes:
        print $_;
      }
    }

    close(FILE);
  }

  exit 0;
}

sub process_source_file($$$)
{
  my ($directory, $source_file, $skip_leading_comments) = @_;
  my $found_start = !$skip_leading_comments;

  print "<para>File: <filename>$source_file</filename> (For use with gtkmm 4)\n";
  print "</para>\n";
  print "<programlisting>\n";

  if (!open(SOURCE_FILE, "$directory/$source_file"))
  {
    print STDERR "Can't open $directory/$source_file\n";
  }

  while(<SOURCE_FILE>)
  {
    # Skip all text until the first code line.
    if(!$found_start)
    {
      next unless /^[#\w]/;
      $found_start = 1;
    }

    s/&/&amp;/g;
    s/</&lt;/g;
    s/>/&gt;/g;
    s/"/&quot;/g;

    print $_;
  }

  close(SOURCE_FILE);

  print "</programlisting>\n";
}
