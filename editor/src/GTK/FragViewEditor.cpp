// #include <Windows/SplashWindow.h>
// #include <Core/Log.h>
// #include <Core/SystemInfo.h>
// #include"FragViewEditor.h"
// #include"Core/gtkconfig.h"

// G_DEFINE_TYPE(FragViewEditorApp, fragview_editor_app, GTK_TYPE_APPLICATION)

// void fragview_editor_app_init(_FragViewEditorApp *app) {
// 	/*  Create root window. */
// 	SplashWindow* splashWindow;

// }

// FragViewEditorAppWindow *
// example_app_window_new(FragViewEditorApp *app) {
// 	return (FragViewEditorAppWindow *) g_object_new(fragview_app_window_get_type(), "application", app, NULL);
// }


// static void
// preferences_activated (GSimpleAction *action,
//                        GVariant      *parameter,
//                        gpointer       app)
// {
// }

// static void
// quit_activated (GSimpleAction *action,
//                 GVariant      *parameter,
//                 gpointer       app)
// {
// 	g_application_quit (G_APPLICATION (app));
// }


// static GActionEntry app_entries[] =
// 		{
// 				{ "preferences", preferences_activated, NULL, NULL, NULL },
// 				{ "quit", quit_activated, NULL, NULL, NULL }
// 		};

// static void
// fragview_editor_app_startup (GApplication *app)
// {
// 	GtkBuilder *builder;
// 	GMenuModel *app_menu;
// 	const gchar *quit_accels[] = { "<Ctrl>Q", "<Ctrl>Z", "<Ctrl>Y", NULL};

// 	g_application_mark_busy(app);
// 	G_APPLICATION_CLASS (fragview_editor_app_parent_class)->startup (app);

// 	g_action_map_add_action_entries (G_ACTION_MAP (app),
// 	                                 app_entries, G_N_ELEMENTS (app_entries),
// 	                                 app);
// 	gtk_application_set_accels_for_action (GTK_APPLICATION (app),
// 	                                       "app.quit",
// 	                                       quit_accels);

// 	builder  = gtk_builder_new_from_file("/home/voldie/projects/fragview/editor/res/app-menu.ui");
// 	//builder = gtk_builder_new_from_resource ("/org/gtk/fragview-editor-app/res/app-menu.ui");
// 	app_menu = G_MENU_MODEL (gtk_builder_get_object (builder, "appmenu"));
// 	gtk_application_set_menubar (GTK_APPLICATION (app), app_menu);
// 	//gtk_application_window_set_help_overlay()
// 	g_object_unref (builder);

// 	g_application_unmark_busy(app);
// }

// void
// example_app_window_open(FragViewEditorAppWindow *win,
//                         GFile *file) {
// 	gchar *basename;
// 	GtkWidget *scrolled, *view;
// 	gchar *contents;
// 	gsize length;

// 	basename = g_file_get_basename(file);

// 	scrolled = gtk_scrolled_window_new(NULL, NULL);
// 	gtk_widget_set_hexpand(scrolled, TRUE);
// 	gtk_widget_set_vexpand(scrolled, TRUE);
// 	view = gtk_text_view_new();
// 	gtk_text_view_set_editable(GTK_TEXT_VIEW (view), FALSE);
// 	gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW (view), FALSE);
// 	gtk_container_add(GTK_CONTAINER (scrolled), view);
// 	//gtk_stack_add_titled (GTK_STACK (win->stack), scrolled, basename, basename);

// 	if (g_file_load_contents(file, NULL, &contents, &length, NULL, NULL)) {
// 		GtkTextBuffer *buffer;

// 		buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (view));
// 		gtk_text_buffer_set_text(buffer, contents, length);
// 		g_free(contents);
// 	}

// 	g_free(basename);
// }

// void
// fragview_editor_app_activate(GApplication *app) {


// 	FragViewEditorAppWindow *win;
// 	//GTKRendererWindow* gtkRendererWindow = new GTKRendererWindow();


// 	/*  */
// 	win = example_app_window_new(FRAGVIEWEDITOR_APP(app));
// 	gtk_window_present(GTK_WINDOW (win));

// 	// KIll the splash window.o
// 	GNotification* notification = g_notification_new("hell");
// 	g_application_send_notification(app, "lunch-is-ready", notification);
// 	g_object_unref (notification);
// }

// void
// fragview_editor_app_open(GApplication *app,
//                          GFile **files,
//                          gint n_files,
//                          const gchar *hint) {
// 	GList *windows;
// 	FragViewEditorAppWindow *win;
// 	int i;

// 	windows = gtk_application_get_windows(GTK_APPLICATION (app));
// 	if (windows)
// 		win = FRAGVIEWEDITOR_APP_WINDOW(windows->data);
// 	else
// 		win = example_app_window_new(FRAGVIEWEDITOR_APP(app));

// 	for (i = 0; i < n_files; i++)
// 		example_app_window_open(win, files[i]);

// 	gtk_window_present(GTK_WINDOW (win));
// }

// int gcommand_line(GApplication *application,
//                   GApplicationCommandLine *command_line) {

// }

// void
// fragview_editor_app_class_init(FragViewEditorAppClass *gtk_class) {
// 	G_APPLICATION_CLASS (gtk_class)->startup = fragview_editor_app_startup;
// 	G_APPLICATION_CLASS (gtk_class)->activate = fragview_editor_app_activate;
// 	G_APPLICATION_CLASS (gtk_class)->open = fragview_editor_app_open;
// 	G_APPLICATION_CLASS (gtk_class)->command_line = gcommand_line;
// 	//G_APPLICATION_CLASS (gtk_class)->local_command_line = NULL;
// //	G_APPLICATION_CLASS (gtk_class)->quit_mainloop = NULL;
// //	G_APPLICATION_CLASS (gtk_class)->run_mainloop = NULL;
// }

// const char *application_id = "org.gtk.fragview-editor-app";
// using namespace fragview;

// FragViewEditor::FragViewEditor(SplashWindow* splashWindow, int argc, const char **argv) {
// 	this->root = new EditorWindow();

// 	this->root->showWindow();
// 	this->root->focus();
// 	this->root->setTitle("FragEditor");
// 	FragViewEditorApp *app;

// 	//	this->config = Config::createConfig(argc, argv, Config::getConfigFilePath(argc, argv));

// 	//	/*  Initialize HPM.  */
// 	//	if (!Hpm::init((Hpm::HPMSIMD) this->config->get<int>("SIMD")))
// 	//		throw RuntimeException("Failed to initialize the hpm library.");
// 	//	Log::log(Log::eVerbose, "HPM SIMD using: %s\n", hpm_get_simd_symbol(hpm_get_simd()));

// 	//gtk_major_version()
// //	/*  Verbose information.    */
// 	Log::log(Log::eVerbose, "Platform: %s\n", SystemInfo::getOperatingSystemName(SystemInfo::getOperatingSystem()));
// 	Log::log(Log::eVerbose, "Memory: %d MB\n", SystemInfo::systemMemorySize());
// 	Log::log(Log::eVerbose, "Cache line: %d bytes\n", SystemInfo::getCPUCacheLine());

// 	g_setenv("GSETTINGS_SCHEMA_DIR", ".", FALSE);
// 	int status;
// 	if (g_application_id_is_valid(application_id)) {

// 		app = (FragViewEditorApp *) g_object_new(FRAGVIEW_GET_APP_TYPE,
// 		                                          "application-id", application_id,
// 		                                          "flags", G_APPLICATION_HANDLES_OPEN,
// 		                                          NULL);
// 		GApplication *gapp = G_APPLICATION (app);

// 		//TODO add splash screen during loading.

// 		/*  Set options.    */
// 		g_application_set_inactivity_timeout(gapp, 10);
// 		g_application_set_option_context_parameter_string(gapp, "");
// 		g_application_set_option_context_summary(gapp, "");
// 		//g_application_set_resource_base_path(gapp, NULL);

// 		status = g_application_run(gapp, argc, (char **) argv);
// 		g_object_unref(gapp);
// 	}
// }

// void FragViewEditor::run(void) {
// //	/*  Read first options.   */
// //	this->config = Config::createConfig(argc, argv, Config::getConfigFilePath(argc, argv));
// //
// //	/*  Verbose information.    */
// //	Log::log(Log::eVerbose, "Platform: %s\n", SystemInfo::getOperatingSystemName(SystemInfo::getOperatingSystem()));
// //	Log::log(Log::eVerbose, "Memory: %d MB\n", SystemInfo::systemMemorySize());
// //	Log::log(Log::eVerbose, "Cache line: %d bytes\n", SystemInfo::getCPUCacheLine());
// //
// //	/*  Initialize HPM.  */
// //	if (!Hpm::init((Hpm::HPMSIMD) this->config->get<int>("SIMD")))
// //		throw RuntimeException("Failed to initialize the hpm library.");
// //	Log::log(Log::eVerbose, "HPM SIMD using: %s\n", hpm_get_simd_symbol(hpm_get_simd()));
// //
// //	/*  Create rendering interface. */
// //	const IConfig& renderConfig = config->getSubConfig("render-driver");
// //	this->renderer = Ref<IRenderer>(RenderingFactory::createRendering(config->get<const char *>("renderer-dynamicInterface"), &renderConfig));
// //	Log::log(Log::eVerbose, "Loading Renderer: %s-%s\n", (*this->renderer)->getName().c_str(), (*this->renderer)->getVersion());
// //	Log::log(Log::eVerbose, "API Internal API version: %s\n", (*this->renderer)->getAPIVersion());
// //	(*this->renderer)->setVSync(renderConfig.get<bool>("v-sync"));
// //
// //	/*  Create task scheduler.  */
// //	this->sch = (schTaskSch *) malloc(sizeof(schTaskSch));
// //	int sch = schCreateTaskPool(this->sch, 2, SCH_FLAG_NO_AFM, 48);
// //	if (sch != SCH_OK)
// //		throw RuntimeException(schErrorMsg(status));
// //	sch = schRunTaskSch(this->sch);
// //	if (sch != SCH_OK)
// //		throw RuntimeException(schErrorMsg(status));
// //
// //	//TODO add support for some kind of filesystem.
// //	/*  Create file notify.    */
// //	if (this->config->get<bool>("notify-file"))
// //		this->notify = new FileNotify(this->sch);
// }
