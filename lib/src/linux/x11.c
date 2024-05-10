#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <unistd.h>
#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

int main()
{
    int num_sizes;
    Rotation current_rotation;

    Display *dpy = XOpenDisplay(NULL);
    Window root = RootWindow(dpy, 0);
    XRRScreenSize *xrrs = XRRSizes(dpy, 0, &num_sizes);
    //
    //     GET CURRENT RESOLUTION AND FREQUENCY
    //
    XRRScreenConfiguration *conf = XRRGetScreenInfo(dpy, root);
    short current_rate = XRRConfigCurrentRate(conf);
    SizeID current_size_id = XRRConfigCurrentConfiguration(conf, &current_rotation);

    int current_width = xrrs[current_size_id].width;
    int current_height = xrrs[current_size_id].height;
    std::cout << "current_rate = " << current_rate << std::endl;
    std::cout << "current_width = " << current_width << std::endl;
    std::cout << "current_height = " << current_height << std::endl;

    XCloseDisplay(dpy);
}

#include <X11/Xlib.h>
#include <X11/extensions/Xrandr.h>

int main(int argc, char *argv[])
{
  Display *display = XOpenDisplay(NULL);
  Window default_root_window = XDefaultRootWindow(display);

  XRRScreenResources *screen_resources = XRRGetScreenResources(display, default_root_window);

  RRMode active_mode_id = 0;
  for (int i = 0; i < screen_resources->ncrtc; ++i) {
    XRRCrtcInfo *crtc_info = XRRGetCrtcInfo(display, screen_resources, screen_resources->crtcs[i]);
    // If None, then is not displaying the screen contents
    if (crtc_info->mode != None) {
      active_mode_id = crtc_info->mode; 
    }
  }

  double active_rate = 0;
  for (int i = 0; i < screen_resources->nmode; ++i) {
    XRRModeInfo mode_info = screen_resources->modes[i];
    if (mode_info.id == active_mode_id) {
      active_rate = (double)mode_info.dotClock / ((double)mode_info.hTotal * (double)mode_info.vTotal);
    }
  }

  printf("Active rate is: %.1f\n", active_rate);

  return 0;
}