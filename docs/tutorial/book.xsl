<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:import href="http://docbook.sourceforge.net/release/xsl/current/html/chunk.xsl"/>

  <!-- This is needed to add C++ syntax highlighting to code -->
  <xsl:template name="system.head.content">
    <link rel="stylesheet" href="highlight.min.css"/>
    <script src="highlight.min.js"/>
    <script>
      hljs.configure({languages: ['cpp']});
      hljs.highlightAll();
    </script>
  </xsl:template>
</xsl:stylesheet>
