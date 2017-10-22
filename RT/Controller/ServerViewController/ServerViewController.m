//
//  ServerViewController.m
//  RT
//
//  Created by Macintosh OS X on 10.10.17.
//  Copyright © 2017 UNIT. All rights reserved.
//

#import "ServerViewController.h"
#import "RenderViewController.h"
#import "OperationsManager.h"
#import "rt.h"

@interface ServerViewController ()

@property(nonatomic, readonly) int SCREEN_HEIGHT;
@property(nonatomic, readonly) int SCREEN_WIDTH;
@property (weak) IBOutlet NSPopUpButton *resolutionPopUP;
//@property (weak) IBOutlet WebView *webView;
@property (weak) IBOutlet NSTextField *udpPort;
@property (weak) IBOutlet NSTextField *tcpPort;
@property (weak) IBOutlet WebView *backgroundView;

@end

@implementation ServerViewController

- (void)viewDidLoad {
    [super viewDidLoad];
	
	NSString *path = [[NSBundle mainBundle] pathForResource:@"background" ofType:@"html"];
	NSURL *url = [NSURL fileURLWithPath:path];
	[[_backgroundView mainFrame] loadRequest:[NSURLRequest requestWithURL:url]];
    _SCREEN_HEIGHT = 800;
    _SCREEN_WIDTH = 800;
	//dispatch_queue_t async_animation = dispatch_queue_create("animation", NULL);
}

- (BOOL) validatePort:(NSString *)value {
	
	NSLocale *locale = [NSLocale currentLocale];
	NSString *thousandSeparator = [locale objectForKey:NSLocaleGroupingSeparator];
	NSString *result = [value stringByReplacingOccurrencesOfString:thousandSeparator withString:@""];
	
	NSString *doubleRegex = @"^[0-9]{4}$";
	NSPredicate *doublePredicate = [NSPredicate predicateWithFormat:@"SELF MATCHES %@", doubleRegex];
	return [doublePredicate evaluateWithObject: result];
}

- (IBAction)didPressButton:(NSButton *)sender {
	
	char udpPortEmpty = (char)@([OperationsManager IsEmpty: _udpPort.stringValue]).integerValue;
	char tcpPortEmpty = (char)@([OperationsManager IsEmpty: _tcpPort.stringValue]).integerValue;
	
	if (udpPortEmpty || tcpPortEmpty || ![self validatePort:_tcpPort.stringValue] || ![self validatePort:_udpPort.stringValue] || [_tcpPort integerValue] < 1024 || [_udpPort integerValue] < 1024) {
		[OperationsManager displayError: @"Invalid ports" : @"Please enter valid port [4 digits only bigger than 1024]"];
		return;
	}
	
	int item = (int)[_resolutionPopUP indexOfSelectedItem];

	//_path = [self searchObjectPath];
	//char *scene = (char*)[_path cStringUsingEncoding:[NSString defaultCStringEncoding]];
    
    InfoSingleton *manager = [InfoSingleton shared];
	
	switch (item) {
        case 0:
            _SCREEN_WIDTH = 800;
            _SCREEN_HEIGHT = 800;
            break ;
        case 1:
            _SCREEN_WIDTH = 1280;
            _SCREEN_HEIGHT = 720;
            break ;
        case 2:
            _SCREEN_WIDTH = 1280;
            _SCREEN_HEIGHT = 1024;
            break ;
		case 4:
			_SCREEN_WIDTH = 1920;
			_SCREEN_HEIGHT = 1080;
            break ;
		case 3:
			_SCREEN_WIDTH = 1366;
			_SCREEN_HEIGHT = 768;
            break ;
		default:
			_SCREEN_WIDTH = 800;
			_SCREEN_HEIGHT = 800;
            break ;
	}
    
    manager.information->image_width = _SCREEN_WIDTH;
    manager.information->image_height = _SCREEN_HEIGHT;
	manager.information->port = __builtin_strdup((char*)[[_udpPort stringValue] cStringUsingEncoding:[NSString defaultCStringEncoding]]);
	manager.information->tcp_port = (int)[_tcpPort integerValue];
	
	[self performSegueWithIdentifier: @"ShowScenesVC" sender: self];
}

-(void)viewWillDisappear {
	
	NSLog(@"%s", "Byebye ServerViewController");
}

//-(void)prepareForSegue:(NSStoryboardSegue *)segue sender:(id)sender {
//
//
//
//		[self removeFromParentViewController];
//    }
//}

//-(NSString*)searchObjectPath {
//
//	NSString *pathString;
//
//	switch ([_mapSelection indexOfSelectedItem]) {
//		case 1:
//			pathString = @"paraboloid";
//			break;
//		case 2:
//			pathString = @"bh";
//			break;
//		case 3:
//			pathString = @"bocuelipse_env";
//			break;
//		case 4:
//			pathString = @"refl_transp";
//			break;
//		case 5:
//			pathString = @"limited_objects";
//			break;
//		case 6:
//			pathString = @"dna";
//			break;
//		case 7:
//			pathString = @"bocuelipse";
//			break;
//		case 8:
//			pathString = @"disturbances";
//			break;
//		case 9:
//			pathString = @"negative_check";
//			break;
//		case 10:
//			pathString = @"ex_obj";
//			break;
//		case 11:
//			pathString = @"tetrahedron";
//			break;
//		case 12:
//			pathString = @"octahedron";
//			break;
//		case 13:
//			pathString = @"bocal_env";
//			break;
//		case 14:
//			pathString = @"textures";
//			break;
//		case 15:
//			pathString = @"env_map_torus";
//			break;
//		case 16:
//			pathString = @"cubehole";
//			break;
//		case 17:
//			pathString = @"solar";
//			break;
//		case 18:
//			pathString = @"sphere";
//			break;
//		case 19:
//			pathString = @"cubohedron";
//			break;
//		case 20:
//			pathString = @"env_map";
//			break;
//		case 21:
//			pathString = @"heart";
//			break;
//		case 22:
//			pathString = @"moebius";
//			break;
//		case 23:
//			pathString = @"box";
//			break;
//		case 24:
//			pathString = @"rgb";
//			break;
//		case 25:
//			pathString = @"bocal";
//			break;
//		default:
//			pathString = @"torus";
//			break;
//	}
//
//	NSString *path = [[NSBundle mainBundle] pathForResource: pathString ofType:@"json"];
//
//	return path;
//}

@end
