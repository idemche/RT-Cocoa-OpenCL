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

@property (weak) IBOutlet WebView *dnaWebView;
@property (weak) IBOutlet WebView *glossyWebView;
@property (weak) IBOutlet WebView *bocalWebView;

@property (weak) IBOutlet WebView        *octaWebView;
@property (weak) IBOutlet NSButton        *octaButton;
@property (nonatomic, strong) NSString *pathString;
@property (nonatomic, assign) NSInteger index;

@end

@implementation ScenesViewController

@synthesize octaWebView = _octaWebView;
@synthesize pathString = _pathString;
@synthesize index = _index;

- (void)viewDidLoad {
    
    [super viewDidLoad];
    
    dispatch_queue_t async_animation = dispatch_queue_create("animation", NULL);

    dispatch_async(async_animation, ^{
        NSString *path_dna = [[NSBundle mainBundle] pathForResource:@"dna" ofType:@"html"];
        NSURL *url_dna = [NSURL fileURLWithPath:path_dna];
        [[_dnaWebView mainFrame] loadRequest:[NSURLRequest requestWithURL:url_dna]];
		
		NSString *path_glossy = [[NSBundle mainBundle] pathForResource:@"glossy_plane" ofType:@"html"];
		NSURL *url_glossy = [NSURL fileURLWithPath:path_glossy];
		[[_glossyWebView mainFrame] loadRequest:[NSURLRequest requestWithURL:url_glossy]];
		
		
		NSString *path_bocal = [[NSBundle mainBundle] pathForResource:@"bocal" ofType:@"html"];
		NSURL *url = [NSURL fileURLWithPath:path_bocal];
		[[_bocalWebView mainFrame] loadRequest:[NSURLRequest requestWithURL:url]];
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
        manager.information->keys.change_scene = (int)[self returnUpdateScene: _pathString];
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
        manager.information->keys.change_scene = (int)[self returnUpdateScene: _pathString];
    }
}
- (IBAction)didPressBocuelipse:(NSButton *)sender { //Glossy Plane Now
    _pathString = [[NSBundle mainBundle] pathForResource: @"glossy_plane" ofType:@"json"];
    if (!((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated)
    {
        [self returnScene:_pathString];
        ((InfoSingleton*)[InfoSingleton shared]).serverIsInitiated = 1;
        [self performSegueWithIdentifier: @"ShowRenderer" sender: self];
    }
    else {
        InfoSingleton *manager = [InfoSingleton shared];
        manager.information->keys.change_scene = (int)[self returnUpdateScene: _pathString];
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
        manager.information->keys.change_scene = (int)[self returnUpdateScene: _pathString];
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
        manager.information->keys.change_scene = (int)[self returnUpdateScene: _pathString];
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
        manager.information->keys.change_scene = (int)[self returnUpdateScene: _pathString];
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
        manager.information->keys.change_scene = (int)[self returnUpdateScene: _pathString];
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
        manager.information->keys.change_scene = (int)[self returnUpdateScene: _pathString];
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
        manager.information->keys.change_scene = (int)[self returnUpdateScene: _pathString];
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
        manager.information->keys.change_scene = (int)[self returnUpdateScene: _pathString];
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
        manager.information->keys.change_scene = (int)[self returnUpdateScene: _pathString];
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
        manager.information->keys.change_scene = (int)[self returnUpdateScene: _pathString];
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
        manager.information->keys.change_scene = (int)[self returnUpdateScene: _pathString];
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
        manager.information->keys.change_scene = (int)[self returnUpdateScene: _pathString];
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
        manager.information->keys.change_scene = (int)[self returnUpdateScene: _pathString];
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
        manager.information->keys.change_scene = (int)[self returnUpdateScene: _pathString];
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
        manager.information->keys.change_scene = (int)[self returnUpdateScene: _pathString];
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
        manager.information->keys.change_scene = (int)[self returnUpdateScene: _pathString];
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
        manager.information->keys.change_scene = (int)[self returnUpdateScene: _pathString];
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
        manager.information->keys.change_scene = (int)[self returnUpdateScene: _pathString];
    }
}

- (void)prepareForSegue:(NSStoryboardSegue *)segue sender:(id)sender {
	
	if ([segue.identifier isEqualToString: @"ShowRenderer"]) {
		
		NSArray<NSWindow*> *windows = NSApplication.sharedApplication.windows;
		
		for (NSWindow *to_close in windows) {
			
			NSString *str = [to_close className];
			
			SWITCH (str) {
				
				CASE (@"SDLWindow") {
					
					break;
				}
				
				DEFAULT {
					
					[to_close close];
					break;
				}
			}
		}
	}
}


@end
