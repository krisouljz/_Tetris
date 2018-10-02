//
//  Demo6VC.swift
//  Tetris_Example
//
//  Created by Junren Wong on 2018/10/2.
//  Copyright © 2018 wangjunren. All rights reserved.
//
import UIKit


class Demo6Inter : IntercepterAdapter, IIntercepterComponent {
    
    required override init() {
        super.init()
    }

    override func matchUrlPatterns() -> [String]? {
        return ["^/swift/demo6\\??.*"]
    }
    
    
    override func doAdjudgement(_ judger: IIntercepterJudger) {
        if let userId = judger.intent().getString("userId"), userId.count > 0 {
            judger.doContinue()
            return
        }
        
        let intent = Intent.pushPop(byUrl: "/login/demo6")!
        intent.displayer = judger.intent().displayer
        intent
            .onResult
            .subscribe({_ in
                judger.intent().extraParameters.addEntries(from: ["userId" : "userId"])
                judger.restart()
            })
        
        judger.doSwitch(intent)
        
    }
    
    
}


class Demo6VC: BaseVC, IRouterComponent {

    class var routeURLs: [URLPresentable] {
        return ["/swift/demo6"]
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
    }

    override func viewDidAppear(_ animated: Bool) {
        super.viewDidDisappear(animated)
        if let f = self.ts_sourceIntent.urlComponent?.fragment {
            alert(msg: f)
        }
    }
    
}
