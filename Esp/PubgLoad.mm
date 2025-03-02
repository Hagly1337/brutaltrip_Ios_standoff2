//
//  PubgLoad.m
//  pubg
//
//  Created by 李良林 on 2021/2/14.
//

#import "PubgLoad.h"
#import <UIKit/UIKit.h>

#import "JHPP.h"
#import "JHDragView.h"
#import "ImGuiLoad.h"
#import "ImGuiDrawView.h"

#define timer(sec) dispatch_after(dispatch_time(DISPATCH_TIME_NOW, sec * NSEC_PER_SEC), dispatch_get_main_queue(), ^

@interface PubgLoad()
@property (nonatomic, strong) ImGuiDrawView *vna;
@end

@implementation PubgLoad

static PubgLoad *extraInfo;



bool isOpened = false;
bool overlay = false;

+ (void)load
{
[super load];



    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(3* NSEC_PER_SEC)), dispatch_get_main_queue(), ^{

            extraInfo =  [PubgLoad new];
            [extraInfo initTapGes];
            [extraInfo tapIconView];
            [extraInfo initTapGes2];
            [extraInfo tapIconView2];
        });

    }


-(void)initTapGes
{


    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] init];
    tap.numberOfTapsRequired = 2;//点击次数
    tap.numberOfTouchesRequired = 3;//手指数
    [[JHPP currentViewController].view addGestureRecognizer:tap];
    [tap addTarget:self action:@selector(tapIconView)];
}

-(void)initTapGes2
{
    UITapGestureRecognizer *tap = [[UITapGestureRecognizer alloc] init];
    tap.numberOfTapsRequired = 2;//点击次数
    tap.numberOfTouchesRequired = 4;//手指数
    [[JHPP currentViewController].view addGestureRecognizer:tap];
    [tap addTarget:self action:@selector(tapIconView2)];
}

-(void)tapIconView
{
 if (!_vna) {
     ImGuiDrawView *vc = [[ImGuiDrawView alloc] init];
     _vna = vc;
 }
 isOpened = !isOpened;
 [ImGuiDrawView showChange:isOpened];
 [[UIApplication sharedApplication].windows[0].rootViewController.view addSubview:_vna.view];

}

-(void)tapIconView2
{
 if (!_vna) {
     ImGuiDrawView *vc = [[ImGuiDrawView alloc] init];
     _vna = vc;
 }

 overlay = !overlay;
 if (overlay) {
     UIView *pmtview = [UIView new];
     pmtview.frame = [UIApplication sharedApplication].keyWindow.frame;
     [pmtview setBackgroundColor:[UIColor clearColor]];
     [pmtview setUserInteractionEnabled:NO];
     UITextField *pmtfield = [[UITextField alloc]init];
     pmtfield.secureTextEntry = true;
     [pmtview addSubview:pmtfield];
     pmtview = pmtfield.layer.sublayers.firstObject.delegate;
     [pmtview addSubview:_vna.view];

     [[UIApplication sharedApplication].windows[0].rootViewController.view addSubview:pmtview];
 } else {
     [[UIApplication sharedApplication].windows[0].rootViewController.view addSubview:_vna.view];
 }
 [ImGuiDrawView showOverlay:overlay];
}
@end
