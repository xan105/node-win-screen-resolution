
#include <wayland-client.h>
#include <napi.h>

Napi::ThreadSafeFunction threadSafeCallback;

struct ctx {
  struct wl_list outputs;
};

struct output_t {
  int id;
  struct ctx *ctx;
  struct wl_output *output;
  struct wl_list link;
};

static void output_handle_geometry(void *data, struct wl_output *wl_output, int32_t x, int32_t y, int32_t physical_width, int32_t physical_height, int32_t subpixel, const char *make, const char *model, int32_t output_transform) {
  struct output_t *out = (struct output_t *)data;

  //https://jakecyr.medium.com/saving-javascript-callbacks-with-node-addon-api-3c6e804aa367

  printf("output %d\n---------\n", out->id);

  printf("x: %d\n", x);
  printf("y: %d\n", y);
  printf("physical_width: %d\n", physical_width);
  printf("physical_height: %d\n", physical_height);
  printf("subpixel: %d\n", subpixel);
  printf("make: %s\n", make);
  printf("model: %s\n", model);
}

static void output_handle_mode(void *data, struct wl_output *wl_output, uint32_t flags, int32_t width, int32_t height, int32_t refresh) {
  struct output_t *out = (struct output_t *)data;
  printf("output %d\n---------\n", out->id);
  
  printf("width: %d\n", width);
  printf("height: %d\n", height);
  printf("refresh: %.f Hz,\n",(float) refresh / 1000);
}

static void output_handle_done(void *data, struct wl_output *wl_output) {}

static void output_handle_scale(void *data, struct wl_output *wl_output, int32_t scale) {}

static const struct wl_output_listener output_listener = {
    output_handle_geometry, 
    output_handle_mode, 
    output_handle_done,
    output_handle_scale,
};

static void global_registry_handler(void *data, struct wl_registry *registry, uint32_t id, const char *interface, uint32_t version) {
  if (!strcmp(interface, "wl_output")) {
    struct ctx *ctx = (struct ctx *)data;
    struct output_t *output = malloc(sizeof(struct output_t));
    output->ctx = ctx;
    output->id = id;
    output->output = wl_registry_bind(registry, id, &wl_output_interface, version);
    wl_list_insert(&ctx->outputs, &output->link);
    wl_output_add_listener(output->output, &output_listener, output);
  }
}

static void global_registry_remover(void *data, struct wl_registry *registry, uint32_t id) {}

static const struct wl_registry_listener registry_listener = {
  global_registry_handler, 
  global_registry_remover
};
    
function(){

  Napi::Env env = info.Env();

  //info checking

  Napi::Function callback = info[0].As<Napi::Function>();

  threadSafeCallback = Napi::ThreadSafeFunction::New(env, callback, "Callback", 0, 1);

  struct wl_display *display = wl_display_connect(NULL);
  if (display == NULL) {
    Napi::Error::New(env, "Failed to connect to the default Wayland socket").ThrowAsJavaScriptException();
  }
  
  struct ctx ctx;
  wl_list_init(&ctx.outputs);

  struct wl_registry *registry = wl_display_get_registry(display);
  wl_registry_add_listener(registry, &registry_listener, &ctx);
  
  wl_display_dispatch(display);
  wl_display_roundtrip(display);
  
  struct output_t *out, *tmp;
  wl_list_for_each_safe(out, tmp, &ctx.outputs, link) {
    wl_output_destroy(out->output);
    wl_list_remove(&out->link);
    free(out);
  }
  wl_registry_destroy(registry);
  wl_display_disconnect(display);
}