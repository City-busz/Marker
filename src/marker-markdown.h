/*
 * marker-markdown.h
 *
 * Copyright (C) 2017 - 2018 Fabio Colacio
 *
 * Marker is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 *
 * Marker is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with Marker; see the file LICENSE.md. If not,
 * see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __MARKER_MARKDOWN_H__
#define __MARKER_MARKDOWN_H__

#include <stddef.h>
#include "scidown/src/document.h"

typedef enum {
  MATHJS_OFF,
  MATHJS_NET,
  MATHJS_LOCAL
} MarkerMathJSMode;

typedef enum{
  HIGHLIGHT_OFF,
  HIGHLIGHT_NET,
  HIGHLIGHT_LOCAL
} MarkerHighlightMode;

typedef enum{
  MERMAID_OFF,
  MERMAID_NET,
  MERMAID_LOCAL
} MarkerMermaidMode;

char                *marker_markdown_css                         (const char         *stylesheet_location);
char                *marker_markdown_scidown_css                 ();

char                *marker_markdown_to_html                     (const char         *markdown,
                                                                  size_t              size,
                                                                  char               *base_folder,
                                                                  MarkerMathJSMode     katex_mode,
                                                                  MarkerHighlightMode highlight_mode,
                                                                  MarkerMermaidMode   mermaid_mode,
                                                                  const char         *stylesheet_location,
                                                                  int                 cursor_position);

char                *marker_markdown_to_html_with_css_inline     (const char         *markdown,
                                                                  size_t              size,
                                                                  char               *base_folder,
                                                                  MarkerMathJSMode     katex_mode,
                                                                  MarkerHighlightMode highlight_mode,
                                                                  MarkerMermaidMode   mermaid_mode,
                                                                  const char         *stylesheet_location,
                                                                  int                 cursor_position);

char                *marker_markdown_to_latex                    (const char         *markdown,
                                                                  size_t              size,
                                                                  char               *base_folder,
                                                                  MarkerMathJSMode     katex_mode,
                                                                  MarkerHighlightMode highlight_mode,
                                                                  MarkerMermaidMode   mermaid_mode,
                                                                  const char         *stylesheet_location);

void                 marker_markdown_to_html_file                (const char         *markdown,
                                                                  size_t              size,
                                                                  char               *base_folder,
                                                                  MarkerMathJSMode     katex_mode,
                                                                  MarkerHighlightMode highlight_mode,
                                                                  MarkerMermaidMode   mermaid_mode,
                                                                  const char         *stylesheet_location,
                                                                  const char         *filepath);

void                 marker_markdown_to_html_file_with_css_inline(const char         *markdown,
                                                                  size_t              size,
                                                                  char               *base_folder,
                                                                  MarkerMathJSMode     katex_mode,
                                                                  MarkerHighlightMode highlight_mode,
                                                                  MarkerMermaidMode   mermaid_mode,
                                                                  const char         *stylesheet_location,
                                                                  const char         *filepath);

void                 marker_markdown_to_latex_file               (const char         *markdown,
                                                                  size_t              size,
                                                                  char               *base_folder,
                                                                  MarkerMathJSMode     katex_mode,
                                                                  MarkerHighlightMode highlight_mode,
                                                                  MarkerMermaidMode   mermaid_mode,
                                                                  const char         *filepath);

metadata           *marker_markdown_metadata                     (const char         *markdown,
                                                                  size_t              size);

#endif
