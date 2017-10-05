#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "marker-string.h"
#include "marker-markdown.h"

#include "marker-exporter.h"

MarkerExportFormat
marker_exporter_str_to_fmt(const char* str)
{
  if (strcmp(str, "PDF") == 0)
  {
    return PDF;
  }
  
  if (strcmp(str, "RTF") == 0)
  {
    return RTF;
  }
  
  if (strcmp(str, "ODT") == 0)
  {
    return ODT;
  }
  
  if (strcmp(str, "DOCX") == 0)
  {
    return DOCX;
  }
  
  if (strcmp(str, "LATEX") == 0)
  {
    return LATEX;
  }
  
  return HTML;
}

void
marker_exporter_export_pandoc(const char*        markdown,
                              const char*        stylesheet_path,
                              const char*        outfile,
                              MarkerExportFormat format)
{
  const char* ftmp = ".marker_tmp_markdown.md";
  char* path = marker_string_filename_get_path(outfile);
  if (chdir(path) == 0)
  {
    FILE* fp = NULL;
    fp = fopen(ftmp, "w");
    if (fp)
    {
      fputs(markdown, fp);
      fclose(fp);
      
      const char* format_s = "rtf";
      switch (format)
      {
        case RTF:
          format_s = "rtf";
          break;
          
        case DOCX:
          format_s = "docx";
          break;
          
        case ODT:
          format_s = "odt";
          break;
          
        case LATEX:
          format_s = "latex";
          break;
          
        case HTML:
        case PDF:
        default:
          break;
      }
      
      char* command = NULL;
      
      asprintf(&command,
               "pandoc -s -c %s -t %s -f markdown -o %s %s",
               stylesheet_path,
               format_s,
               outfile,
               ftmp);
      
      if (command)
      {
        system(command);
      }
      
      free(command);
      remove(ftmp);
    }
  }
  free(path);
}

void
marker_exporter_export(const char*        markdown,
                       const char*        stylesheet_path,
                       const char*        outfile,
                       MarkerExportFormat format)
{
  switch (format)
  {
    case HTML:
    {
      puts("test");
      marker_markdown_to_html_file_with_css_inline(markdown,
                                                   strlen(markdown),
                                                   stylesheet_path,
                                                   outfile);
      break;
    }
    
    case PDF:
    {
      break;
    }
    
    case RTF:
    case DOCX:
    case ODT:
    case LATEX:
    default:
      marker_exporter_export_pandoc(markdown, stylesheet_path, outfile, format);
      break;
  }
}

void
marker_exporter_show_export_dialog(GtkWindow*  parent,
                                   const char* markdown,
                                   const char* stylesheet_path)
{
  GtkDialog* dialog;
  dialog = GTK_DIALOG(gtk_file_chooser_dialog_new("Export",
                                                  parent,
                                                  GTK_FILE_CHOOSER_ACTION_SAVE,
                                                  "Cancel",
                                                  GTK_RESPONSE_CANCEL,
                                                  "Export",
                                                  GTK_RESPONSE_ACCEPT,
                                                  NULL));
                                                  
  GtkFileChooser* chooser = GTK_FILE_CHOOSER(dialog);
  gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);
  gtk_file_chooser_set_create_folders(chooser, TRUE);
  gtk_file_chooser_set_select_multiple(chooser, FALSE);
  
  GtkFileFilter* filter = NULL;
  
  filter = gtk_file_filter_new();
  gtk_file_filter_set_name(filter, "HTML");
  gtk_file_filter_add_pattern(filter, "*.html");
  gtk_file_chooser_add_filter(chooser, filter);
  
  filter = gtk_file_filter_new();
  gtk_file_filter_set_name(filter, "PDF");
  gtk_file_filter_add_pattern(filter, "*.pdf");
  gtk_file_chooser_add_filter(chooser, filter);
  
  filter = gtk_file_filter_new();
  gtk_file_filter_set_name(filter, "RTF");
  gtk_file_filter_add_pattern(filter, "*.rtf");
  gtk_file_chooser_add_filter(chooser, filter);
  
  filter = gtk_file_filter_new();
  gtk_file_filter_set_name(filter, "DOCX");
  gtk_file_filter_add_pattern(filter, "*.docx");
  gtk_file_chooser_add_filter(chooser, filter);
  
  filter = gtk_file_filter_new();
  gtk_file_filter_set_name(filter, "ODT");
  gtk_file_filter_add_pattern(filter, "*.odt");
  gtk_file_chooser_add_filter(chooser, filter);
  
  filter = gtk_file_filter_new();
  gtk_file_filter_set_name(filter, "LATEX");
  gtk_file_filter_add_pattern(filter, "*.tex");
  gtk_file_chooser_add_filter(chooser, filter);
  
  filter = NULL;
  
  gint ret = gtk_dialog_run(dialog);
  if (ret == GTK_RESPONSE_ACCEPT)
  {
    gchar* filename = gtk_file_chooser_get_filename(chooser);
    filter = gtk_file_chooser_get_filter(chooser);
    const gchar* file_type = gtk_file_filter_get_name(filter);
    MarkerExportFormat fmt = marker_exporter_str_to_fmt(file_type);
    marker_exporter_export(markdown, stylesheet_path, filename, fmt);
    g_free(filename);
  }
  
  gtk_widget_destroy(GTK_WIDGET(dialog));
}
