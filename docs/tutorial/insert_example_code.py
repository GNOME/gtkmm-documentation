#!/usr/bin/env python3

#                             argv[1]            argv[2:-1]           argv[-1]
# insert_example_code.py <examples_base_dir> <input_xml_files>... <output_xml_file>

import os
import sys
import re
import glob
import shutil

# Where to insert example code.
source_include_pattern = re.compile(
  r'\s*<para><ulink url="&url_examples_base;([/\w]+)">Source Code</ulink></para>\s*(?:<!--\s*Insert\s+(.*?)-->)?')

# First line not part of leading comment in a source code file.
# The comment typically consists of copyright and license text.
start_of_source_pattern = re.compile(r'[#\w]')

def process_source_file(source_directory, source_basename, outfile, skip_leading_comments):
  found_start = not skip_leading_comments
  source_filename = os.path.join(source_directory, source_basename)
  with open(source_filename, mode='r') as srcfile:
    outfile.write('<para>File: <filename>' + source_basename + '</filename> (For use with gtkmm 3)</para>\n')
    outfile.write('<programlisting>\n<![CDATA[')

    for line in srcfile:
      if not found_start:
        # Skip leading comment.
        if not start_of_source_pattern.match(line):
          continue
        found_start = True
      outfile.write(line)

    outfile.write(']]></programlisting>\n')

def insert_example_code(examples_base_dir, input_xml_files, output_xml_file):
  if not isinstance(input_xml_files, list):
    input_xml_files = [input_xml_files]

  with open(output_xml_file, mode='w') as outfile:
    for input_xml_file in input_xml_files:
      with open(input_xml_file, mode='r') as infile:
        for line in infile:
          # Look for
          # <para><ulink url="&url_examples_base;helloworld">Source Code</ulink></para> [<!-- Insert filenames... -->]
          source_include_match = source_include_pattern.match(line)
          if not source_include_match:
            # Print the line without changes.
            outfile.write(line)
          else:
            # Modify the line to remove the trailing comment, if any.
            # url_examples_base is assumed to be a GitLab URL. The git branch is then
            # included in url_examples_base. No need to add it here.
            outfile.write(source_include_match.expand(
              '<para><ulink url="&url_examples_base;\\1">Source Code</ulink></para>\n'))
            outfile.write('<!-- start inserted example code -->\n')

            # List all the source files in the examples directory.
            source_directory = os.path.join(examples_base_dir, source_include_match.group(1))
            for source_filename in glob.glob(os.path.join(source_directory, '*.h')) + \
                                   glob.glob(os.path.join(source_directory, '*.cc')):
              source_basename = os.path.basename(source_filename)
              process_source_file(source_directory, source_basename, outfile, True)

            # And possibly other files in the examples directory.
            if source_include_match.group(2):
              for source_basename in source_include_match.group(2).split():
                process_source_file(source_directory, source_basename, outfile, False)
            outfile.write('<!-- end inserted example code -->\n')
  return 0

# ----- Main -----
if __name__ == '__main__':
  if len(sys.argv) < 4:
    print('Usage: ' + sys.argv[0] + ' <examples_base_dir> <input_xml_files>... <output_xml_file>')
    sys.exit(1)

  sys.exit(insert_example_code(sys.argv[1], sys.argv[2:-1], sys.argv[-1]))
