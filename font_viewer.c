#include <gtk/gtk.h>
#include <fontconfig/fontconfig.h>
#include <pango/pangocairo.h>
#include <pango/pangofc-font.h>

typedef struct {
    GtkWidget *family;
    GtkWidget *style;
    GtkWidget *file;
    GtkWidget *weight;
    GtkWidget *slant;
    GtkWidget *spacing;
    GtkWidget *postscript;
    GtkWidget *pattern;
} FontFields;

static void
set_entry(GtkWidget *entry, const char *text)
{
    if (!GTK_IS_ENTRY(entry))
        return;
    gtk_entry_set_text(GTK_ENTRY(entry), text ? text : "");
}

static void
font_changed_cb(GObject *object, GParamSpec *pspec, gpointer user_data)
{
    (void)pspec;

    FontFields *fields = user_data;
    GtkFontChooser *chooser = GTK_FONT_CHOOSER(object);

    PangoFontDescription *desc = gtk_font_chooser_get_font_desc(chooser);
    if (!desc)
        return;

    PangoContext *context =
        gtk_widget_get_pango_context(GTK_WIDGET(object));
    PangoFontMap *map = pango_context_get_font_map(context);
    PangoFont *font =
        pango_font_map_load_font(map, context, desc);

    if (!font)
        goto out;

    FcPattern *pattern =
        pango_fc_font_get_pattern(PANGO_FC_FONT(font));

    if (!pattern)
        goto out;

    set_entry(fields->family, NULL);
    set_entry(fields->style, NULL);
    set_entry(fields->file, NULL);
    set_entry(fields->weight, NULL);
    set_entry(fields->slant, NULL);
    set_entry(fields->spacing, NULL);
    set_entry(fields->postscript, NULL);
    set_entry(fields->pattern, NULL);

    FcChar8 *str;
    int i;
    char buf[64];
    const char *family_str = NULL;
    const char *style_str = NULL;

    if (FcPatternGetString(pattern, FC_POSTSCRIPT_NAME, 0, &str) == FcResultMatch)
        set_entry(fields->postscript, (char *)str);

    if (FcPatternGetString(pattern, FC_FAMILY, 0, &str) == FcResultMatch) {
        family_str = (char *)str;
        set_entry(fields->family, (char *)str);
    }

    if (FcPatternGetString(pattern, FC_STYLE, 0, &str) == FcResultMatch) {
        style_str = (char *)str;
        set_entry(fields->style, (char *)str);
    }

    if (FcPatternGetString(pattern, FC_FILE, 0, &str) == FcResultMatch)
        set_entry(fields->file, (char *)str);

    if (FcPatternGetInteger(pattern, FC_WEIGHT, 0, &i) == FcResultMatch) {
        g_snprintf(buf, sizeof buf, "%d", i);
        set_entry(fields->weight, buf);
    }

    if (FcPatternGetInteger(pattern, FC_SLANT, 0, &i) == FcResultMatch) {
        g_snprintf(buf, sizeof buf, "%d", i);
        set_entry(fields->slant, buf);
    }

    if (FcPatternGetInteger(pattern, FC_SPACING, 0, &i) == FcResultMatch) {
        set_entry(fields->spacing,
            i == FC_MONO ? "Monospace" :
            i == FC_PROPORTIONAL ? "Proportional" : "Other");
    }

    if (family_str || style_str) {
        char name_buf[128];
        if (family_str && style_str)
            g_snprintf(name_buf, sizeof name_buf, "%s %s", family_str, style_str);
        else
            g_snprintf(name_buf, sizeof name_buf,
                       "%s%s",
                       family_str ? family_str : "",
                       style_str ? style_str : "");
        set_entry(fields->pattern, name_buf);
    }

out:
    if (font)
        g_object_unref(font);
    pango_font_description_free(desc);
}

static GtkWidget *
labeled_entry(GtkWidget **out_entry, const char *label)
{
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
    GtkWidget *lbl = gtk_label_new(label);
    GtkWidget *entry = gtk_entry_new();

    gtk_label_set_xalign(GTK_LABEL(lbl), 0.0);
    gtk_widget_set_size_request(lbl, 100, -1);

    gtk_editable_set_editable(GTK_EDITABLE(entry), FALSE);
    gtk_widget_set_can_focus(entry, TRUE);

    gtk_box_pack_start(GTK_BOX(box), lbl, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box), entry, TRUE, TRUE, 0);

    *out_entry = entry;
    return box;
}

int
main(int argc, char **argv)
{
    gtk_init(&argc, &argv);
    if (!FcInit()) {
        g_printerr("Failed to initialize Fontconfig\n");
        return 1;
    }

    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "GTK3 Font Viewer");
    gtk_window_set_default_size(GTK_WINDOW(window), 700, 500);

    GtkWidget *root = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_container_set_border_width(GTK_CONTAINER(root), 8);

    GtkWidget *chooser = gtk_font_chooser_widget_new();
    gtk_box_pack_start(GTK_BOX(root), chooser, TRUE, TRUE, 0);

    gtk_font_chooser_set_font(GTK_FONT_CHOOSER(chooser), "Sans Regular 14");

    FontFields *fields = g_new0(FontFields, 1);

    GtkWidget *meta = gtk_box_new(GTK_ORIENTATION_VERTICAL, 4);
    gtk_box_pack_start(GTK_BOX(root), meta, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(meta), labeled_entry(&fields->family,  "Family"), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(meta), labeled_entry(&fields->style,   "Style"), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(meta), labeled_entry(&fields->file,    "File"), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(meta), labeled_entry(&fields->weight,  "Weight"), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(meta), labeled_entry(&fields->slant,   "Slant"), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(meta), labeled_entry(&fields->spacing, "Spacing"), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(meta), labeled_entry(&fields->postscript, "PostScript"), FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(meta), labeled_entry(&fields->pattern, "Fontconfig"), FALSE, FALSE, 0);

    g_signal_connect(chooser, "notify::font",
                     G_CALLBACK(font_changed_cb), fields);

    g_signal_connect(window, "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);

    gtk_container_add(GTK_CONTAINER(window), root);
    gtk_widget_show_all(window);

    gtk_main();
    FcFini();
    g_free(fields);
    return 0;
}
