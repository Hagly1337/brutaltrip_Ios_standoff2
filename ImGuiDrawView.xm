#import "Helper/x2nios.h"
#import "Esp/ImGuiDrawView.h"
#import <Metal/Metal.h>
#include "oxorany/oxorany_include.h"
#define FMT_HEADER_ONLY
#include "fmt/core.h"
#import <MetalKit/MetalKit.h>
#import <Foundation/Foundation.h>
#include "KittyMemory/imgui.h"
#include "KittyMemory/imgui_internal.h"
#include "KittyMemory/imgui_impl_metal.h"
#import <Foundation/Foundation.h>
#import <os/log.h>
#import "pthread.h"
#include <math.h>
#include <deque>
#include <vector>
#include <fstream>
#include "Helper/Vector3.h"
#include "Helper/Vector2.h"
#include "Helper/Quaternion.h"
#include "Helper/Monostring.h"
#include <vector>
#import <dlfcn.h>
#include <map>
#include "Helper/font.h"
#include "Helper/data.h"
#include "Helper/il2cpp_api_wrapper.h"
#include "dobby/dobby.h"
#include "encrypt.h"
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#include <unistd.h>
#include <string.h>
ImFont* verdana_small;

#import "Helper/Functions/Hooks.h"


#define kWidth  [UIScreen mainScreen].bounds.size.width
#define kHeight [UIScreen mainScreen].bounds.size.height
#define kScale [UIScreen mainScreen].scale





@interface ImGuiDrawView () <MTKViewDelegate>
//@property (nonatomic, strong) IBOutlet MTKView *mtkView;
@property (nonatomic, strong) id <MTLDevice> device;
@property (nonatomic, strong) id <MTLCommandQueue> commandQueue;

@end
@implementation ImGuiDrawView

ImFont* verdanab;
ImFont* icons;
ImFont* interb;
ImFont* Urbanist;

static bool MenDeal = true;

#define BundlePath @"/Library/PreferenceBundles/Tweak.bundle"
- (instancetype)initWithNibName:(nullable NSString *)nibNameOrNil bundle:(nullable NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];

    _device = MTLCreateSystemDefaultDevice();
    _commandQueue = [_device newCommandQueue];

    if (!self.device) abort();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();
    auto& Style = ImGui::GetStyle();
    io.Fonts->AddFontDefault();

    verdana_small = io.Fonts->AddFontFromMemoryTTF(verdana, sizeof verdana, 60, NULL, io.Fonts->GetGlyphRangesCyrillic());

    ImGui_ImplMetal_Init(_device);

    return self;
}
static bool OverlayEnabled = true;

+ (void)showChange:(BOOL)open
{
    MenDeal = open;
}
+ (void)showOverlay:(BOOL)open
{
    OverlayEnabled = open;
}
static UITextField *Norecord;


- (MTKView *)mtkView
{
    return (MTKView *)self.view;
}

static std::string site_url_encrypted_begin = oxorany("http://185.221.155.95:1337/api/check_key?key_id=");
static std::string valid_string = oxorany("You have been authenticated successfully");
static std::string site_part = oxorany("&game=standoff&hwid=");
static std::string error_404 = oxorany("error: 404");
NSString *site_response;
NSString *key;
bool requested;
static bool auth_scfhqjvfohtqn5cb = false;

void save_key(std::string path, std::string key) {
    std::ofstream outfile(path.c_str());
    outfile << key << std::endl;
    outfile.flush();
    outfile.close();
}

std::string load_key(std::string path) {
    std::string tempstr;
    std::ifstream file(path.c_str());
    file >> tempstr;
    file.close();
    return tempstr;
}

- (NSString *) getDataFrom {
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] init];
    [request setHTTPMethod:nsstring_encrypt("GET")];

    NSUUID* identifierForVendor = [[UIDevice currentDevice] identifierForVendor];
    NSString* hwid = [identifierForVendor UUIDString];
    NSString *nurl = [NSString stringWithFormat:nsstring_encrypt("%@%@%@%@"), [NSString stringWithUTF8String:site_url_encrypted_begin.c_str()],
key, [NSString stringWithUTF8String:site_part.c_str()], hwid];

    [request setURL:[NSURL URLWithString:nurl]];

    NSError *error = nil;
    NSHTTPURLResponse *responseCode = nil;

    NSData *oResponseData = [NSURLConnection sendSynchronousRequest:request returningResponse:&responseCode error:&error];

    if ([responseCode statusCode] != 200)
        site_response = [NSString stringWithUTF8String:error_404.c_str()];

    requested = true;

    return [[NSString alloc] initWithData:oResponseData encoding:NSUTF8StringEncoding];
}

- (void)ShowAlert:(NSString *)text {
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(0.1* NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        UIAlertController *alertController = [UIAlertController alertControllerWithTitle:nsstring_encrypt("t.me/brutaltrip") message:text preferredStyle:UIAlertControllerStyleAlert];

        NSFileManager *filemgr;

        filemgr = [NSFileManager defaultManager];

        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
        NSString *documentsDirectory = [paths objectAtIndex:0];

        std::string key_dir = std::string([documentsDirectory UTF8String]) + oxorany("/user_key");

        UIAlertAction *okAction = [UIAlertAction actionWithTitle:(nsstring_encrypt("Login")) style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
            key = [[alertController textFields][0] text];
            site_response = [self getDataFrom];
            if ([site_response rangeOfString:[NSString stringWithUTF8String:valid_string.c_str()]].location != NSNotFound)
                save_key(key_dir, std::string([key UTF8String]));
        }];
        UIAlertAction *loadAction = [UIAlertAction actionWithTitle:(nsstring_encrypt("Load key")) style:UIAlertActionStyleDefault handler:^(UIAlertAction *action) {
            std::string loaded = load_key(key_dir);
            key = [NSString stringWithUTF8String:loaded.c_str()];//[[alertController textFields][0] text];
            site_response = [self getDataFrom];
        }];

        [alertController addTextFieldWithConfigurationHandler:^(UITextField * _Nonnull textField) {
            textField.placeholder = nsstring_encrypt("Current key");
            textField.secureTextEntry = YES;
        }];
        [alertController addAction:okAction];
        if ([filemgr fileExistsAtPath: [NSString stringWithUTF8String:key_dir.c_str()] ] == YES) [alertController addAction:loadAction];

        UIViewController *rootViewController = [[[UIApplication sharedApplication] keyWindow] rootViewController];
        [rootViewController presentViewController:alertController animated:YES completion:nil];
    });
}

- (void)loadView
{
    CGFloat w = [UIApplication sharedApplication].windows[0].rootViewController.view.frame.size.width;
    CGFloat h = [UIApplication sharedApplication].windows[0].rootViewController.view.frame.size.height;
    self.view = [[MTKView alloc] initWithFrame:CGRectMake(0, 0, w, h)];
}

- (void)viewDidLoad {
    [super viewDidLoad];

    self.mtkView.device = self.device;
    self.mtkView.delegate = self;
    self.mtkView.clearColor = MTLClearColorMake(0, 0, 0, 0);
    self.mtkView.backgroundColor = [UIColor colorWithRed:0 green:0 blue:0 alpha:0];
    self.mtkView.clipsToBounds = YES;

}

void ColorPicker(const char* name, ImVec4 &color) {
    static ImVec4 backup_color;

    bool open_popup = ImGui::ColorButton((std::string(name) + std::string("##3b")).c_str(), color);
    //open_popup |= ImGui::Button("Palette");
    if (open_popup) {
        ImGui::OpenPopup(name);
        backup_color = color;
    }
    if (ImGui::BeginPopup(name)) {
        ImGui::Spacing();
        ImGui::Text("Select Color");
        ImGui::Separator();
        ImGui::ColorPicker4("##picker", (float *) &color,ImGuiColorEditFlags_NoSidePreview |
                                                         ImGuiColorEditFlags_NoSmallPreview);
        ImGui::SameLine();

        ImGui::BeginGroup(); // Lock X position
        ImGui::Text("Current");
        ImGui::ColorButton("##current", color,
                           ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf,
                           ImVec2(60, 40));
        ImGui::Text("Previous");
        if (ImGui::ColorButton("##previous", backup_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60, 40))) {
            color = backup_color;
        }
        ImGui::EndGroup();
        ImGui::EndPopup();
    }
}

#pragma mark - Interaction



- (void)updateIOWithTouchEvent:(UIEvent *)event
{
    UITouch *anyTouch = event.allTouches.anyObject;
    CGPoint touchLocation = [anyTouch locationInView:self.view];
    ImGuiIO &io = ImGui::GetIO();
    io.MousePos = ImVec2(touchLocation.x, touchLocation.y);

    BOOL hasActiveTouch = NO;
    for (UITouch *touch in event.allTouches)
    {
        if (touch.phase != UITouchPhaseEnded && touch.phase != UITouchPhaseCancelled)
        {
            hasActiveTouch = YES;
            break;
        }
    }
    io.MouseDown[0] = hasActiveTouch;




}



- (void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [self updateIOWithTouchEvent:event];
}

- (void)touchesMoved:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [self updateIOWithTouchEvent:event];
}

- (void)touchesCancelled:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [self updateIOWithTouchEvent:event];
}

- (void)touchesEnded:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [self updateIOWithTouchEvent:event];
}



#import "Helper/Functions/Menu.h"

- (void)mtkView:(MTKView*)view drawableSizeWillChange:(CGSize)size
{

}



void hooking(){
game_sdk->init();
//Dobby(oxorany(0x2A90648), hook_hitcast, old_hitcast);
base_addr = getRealOffset(0);
}

void *hack_thread(void *) {
    sleep(5);
    hooking();
    pthread_exit(nullptr);
    return nullptr;
}

void __attribute__((constructor)) initialize() {
    pthread_t hacks;
    pthread_create(&hacks, NULL, hack_thread, NULL);
}

@end
