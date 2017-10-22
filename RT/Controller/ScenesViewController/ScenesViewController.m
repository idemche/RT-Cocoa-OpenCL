//
//  ScenesViewController.m
//  RT
//
//  Created by Igor Demchenko on 10/16/17.
//  Copyright © 2017 UNIT. All rights reserved.
//

#import "ScenesViewController.h"
#import <Quartz/Quartz.h>

@interface ScenesViewController ()

@property (weak) IBOutlet WebView        *octaWebView;
@property (weak) IBOutlet NSButton        *octaButton;
@property (nonatomic, strong) NSString *pathString;
@property (nonatomic, assign) NSInteger index;

@end

@implementation ScenesViewController

@synthesize octaWebView = _octaWebView;

@synthesize bocalaWebView = _bocalWebView;
@synthesize glossyWebView = _glossyWebView;
@synthesize dnaWebView = _dnaWebView;

@synthesize pathString = _pathString;
@synthesize index = _index;

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    dispatch_queue_t async_animation = dispatch_queue_create("animation", NULL);
    
    dispatch_async(async_animation, ^{
        NSString *path = [[NSBundle mainBundle] pathForResource:@"octa" ofType:@"html"];
        NSURL *url = [NSURL fileURLWithPath:path];
        [[_octaWebView mainFrame] loadRequest:[NSURLRequest requestWithURL:url]];
    });
    
    
    //    _octaScene.canDrawSubviewsIntoLayer = YES;
    //    _octaScene.animates = YES;
    //    _octaScene.imageScaling = NSImageScaleNone;
    //    NSImageView *octa = [[NSImageView alloc] initWithFrame: CGRectMake(10, 10, 150, 113)];
    //    octa.imageScaling = NSImageScaleNone;
    //    octa.animates = YES;
    //    octa.image = [NSImage imageNamed:@"Octa"];
    //    octa.canDrawSubviewsIntoLayer = YES;
    //
    //    NSView *view = [[NSView alloc] initWithFrame:CGRectMake(0, 0, 200, 200)];
    //    view.wantsLayer = YES;
    //    [view addSubview:octa];
    //
    //    [[self view] addSubview: view];
    
}

- (void)returnScene:(NSString*)map {
    
    NSString *bundleRoot = [[NSBundle mainBundle] bundlePath];
    InfoSingleton *manager = [InfoSingleton shared];
    
    NSFileManager *fileManager = [NSFileManager defaultManager];
    NSDirectoryEnumerator *direnum = [fileManager enumeratorAtPath:bundleRoot];
    NSString *filename;
    NSString *string;
    
    int i = 0;
    
    while ((filename = [direnum nextObject] )) {
        
        //change the suffix to what you are looking for
        if ([filename hasSuffix:@".json"] && i < 26) {
            
            // Do work here
            string = [NSString stringWithFormat:@"%@/%@", bundleRoot, filename];
            manager.information->scenes[i] = (char*)[string cStringUsingEncoding:[NSString defaultCStringEncoding]];
            if (!__builtin_strcmp([map cStringUsingEncoding:[NSString defaultCStringEncoding]], manager.information->scenes[i])) {
                manager.information->num_scene = i;
            }
            NSLog(@"Files in resource folder: %@", filename);
            i++;
        }
    }
}

-(NSInteger)returnUpdateScene:(NSString*)map {

    InfoSingleton *manager = [InfoSingleton shared];
    for(NSInteger i = 0; i < 26; i++)
    {
        if (!__builtin_strcmp(manager.information->scenes[i], [map cStringUsingEncoding: [NSString defaultCStringEncoding]]))
            return(i);
    }
    return(-1);
}

-(void)viewDidDisappear {
    NSLog(@"Scenes are dead");
}

- (IBAction)didPressOctaScene:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"dna" ofType:@"json"];
    if (!((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        [self returnScene:_pathString];
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = [self returnUpdateScene: _pathString];
    }
}


- (IBAction)didPressBocal:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"bocal" ofType:@"json"];
    if (!((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        [self returnScene:_pathString];
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = [self returnUpdateScene: _pathString];
    }
}
- (IBAction)didPressBocuelipseEnv:(NSButton *)sender { //Glossy Plane Now
    _pathString = [[NSBundle mainBundle] pathForResource: @"glossy_plane" ofType:@"json"];
    if (!((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        [self returnScene:_pathString];
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = [self returnUpdateScene: _pathString];
    }
}

- (IBAction)didPressBox:(NSButton *)sender { //Rtv1 Now
    _pathString = [[NSBundle mainBundle] pathForResource: @"rtv1" ofType:@"json"];
    if (!((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        [self returnScene:_pathString];
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = [self returnUpdateScene: _pathString];
    }
}

- (IBAction)didPressCubehole:(NSButton *)sender { //tetriminoses Now
    _pathString = [[NSBundle mainBundle] pathForResource: @"tetriminoses" ofType:@"json"];
    if (!((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        [self returnScene:_pathString];
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = [self returnUpdateScene: _pathString];
    }
}

- (IBAction)didPressCubohedron:(NSButton *)sender { // Now refl_transp
    _pathString = [[NSBundle mainBundle] pathForResource: @"refl_transp" ofType:@"json"];
    if (!((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        [self returnScene:_pathString];
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = [self returnUpdateScene: _pathString];
    }
}

- (IBAction)didPressDisturbances:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"disturbances" ofType:@"json"];
    if (!((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        [self returnScene:_pathString];
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = [self returnUpdateScene: _pathString];
    }
}

- (IBAction)didPressDna:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"dna" ofType:@"json"];
    if (!((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        [self returnScene:_pathString];
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = [self returnUpdateScene: _pathString];
    }
}
- (IBAction)didPressDof:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"dof" ofType:@"json"];
    if (!((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        [self returnScene:_pathString];
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = [self returnUpdateScene: _pathString];
    }
}

- (IBAction)didPressEnvMapTorus:(NSButton *)sender { // Toruses Now
    _pathString = [[NSBundle mainBundle] pathForResource: @"toruses" ofType:@"json"];
    if (!((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        [self returnScene:_pathString];
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = [self returnUpdateScene: _pathString];
    }
}

- (IBAction)didPressEnvMap:(NSButton *)sender { // textures Now
    _pathString = [[NSBundle mainBundle] pathForResource: @"textures" ofType:@"json"];
    if (!((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        [self returnScene:_pathString];
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = [self returnUpdateScene: _pathString];
    }
}
- (IBAction)didPressExObj:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"ex_obj" ofType:@"json"];
    if (!((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        [self returnScene:_pathString];
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = [self returnUpdateScene: _pathString];
    }
}
- (IBAction)didPressLimitedObjects:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"limited_objects" ofType:@"json"];
    if (!((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        [self returnScene:_pathString];
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = [self returnUpdateScene: _pathString];
    }
}

- (IBAction)didPressMoebius:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"moebius" ofType:@"json"];
    if (!((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        [self returnScene:_pathString];
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = [self returnUpdateScene: _pathString];
    }
}

- (IBAction)didPressNegativeCheck:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"negative" ofType:@"json"];
    if (!((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        [self returnScene:_pathString];
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = [self returnUpdateScene: _pathString];
    }
}

- (IBAction)didPressParaboloid:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"custom" ofType:@"json"];
    if (!((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        [self returnScene:_pathString];
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = [self returnUpdateScene: _pathString];
    }
}

- (IBAction)didPressPyramid:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"pyramide" ofType:@"json"];
    if (!((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        [self returnScene:_pathString];
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = [self returnUpdateScene: _pathString];
    }
}
//++++++++++++
- (IBAction)didPressReflTransp:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"refl_transp" ofType:@"json"];
    [self returnScene:_pathString];
    if (((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = [self returnUpdateScene: _pathString];
    }
}
- (IBAction)didPressRgb:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"rgb" ofType:@"json"];
    [self returnScene:_pathString];
    if (((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = [self returnUpdateScene: _pathString];
    }
}

- (IBAction)didPressTextures:(NSButton *)sender {
    _pathString = [[NSBundle mainBundle] pathForResource: @"textures" ofType:@"json"];
    if (!((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        [self returnScene:_pathString];
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = [self returnUpdateScene: _pathString];
    }
}


@end
