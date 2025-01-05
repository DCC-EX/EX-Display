# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

import subprocess

# Run Doxygen
subprocess.call('doxygen Doxyfile.in', shell=True)

project = 'EX-Display'
copyright = '2024, peteGSX'
author = 'peteGSX'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = [
  'breathe',
  'exhale',
  'sphinx.ext.autodoc',
  'sphinx.ext.graphviz',
]

graphviz_output_format = 'png'

templates_path = ['_templates']
exclude_patterns = []

# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = 'sphinx_rtd_theme'
html_static_path = ['_static']

html_logo = "./_static/images/logo.png"

html_favicon = "./_static/images/favicon.ico"

html_theme_options = {
    'style_nav_header_background': 'white',
    'logo_only': True,
    # Toc options
    'includehidden': True,
    'titles_only': False,
    # 'titles_only': True,
    'collapse_navigation': False,
    # 'navigation_depth': 3,
    'navigation_depth': -1,
    # 'analytics_id': 'G-L5X0KNBF0W',
}

html_context = {
    'display_github': True,
    'github_user': 'DCC-EX',
    'github_repo': 'EX-Display',
    'github_version': 'sphinx/docs/',
}

html_css_files = [
    'css/dccex_theme.css',
    'css/sphinx_design_overrides.css',
]

# -- Breathe configuration -------------------------------------------------

breathe_projects = {
  "EX-Display": "_build/xml/"
}
breathe_default_project = "EX-Display"
breathe_default_members = ()
breathe_use_project_refids = True
breathe_show_include_files = True
breathe_show_grouped_typedefs = True
breathe_use_inheritance_diagram = True
breathe_graph_maxoutdegree = 10
breathe_graph_maxdepth = 5
breathe_use_inheritance_diagram = True
breathe_show_include_graph = True
breathe_show_collaboration_graph = True
breathe_show_programlisting = True

# -- Breathe configuration -------------------------------------------------

exhale_args = {
    # Required arguments
    "containmentFolder":     "./ex-display",
    "rootFileName":          "ex-display_root.rst",
    "doxygenStripFromPath":  "..",
    # Suggested optional arguments
    "createTreeView":        True,
    "treeViewIsBootstrap":   True,
    # Include all the doxygen generated graphs
    "exhaleExecutesDoxygen": False,
    "generateBreatheFileDirectives": True,
}
