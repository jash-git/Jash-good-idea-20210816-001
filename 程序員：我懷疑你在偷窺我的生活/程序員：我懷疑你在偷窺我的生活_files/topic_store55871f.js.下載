function _defineProperty(e,n,t){
return n in e?Object.defineProperty(e,n,{
value:t,
enumerable:!0,
configurable:!0,
writable:!0
}):e[n]=t,e;
}
function _typeof(e){
return e&&"undefined"!=typeof Symbol&&e.constructor===Symbol?"symbol":typeof e;
}
var _extends=Object.assign||function(e){
for(var n=1;n<arguments.length;n++){
var t=arguments[n];
for(var i in t)Object.prototype.hasOwnProperty.call(t,i)&&(e[i]=t[i]);
}
return e;
};
define("appmsg/without_iframe/video_plugin/video_tail_utils.js",["biz_wap/utils/ajax.js","biz_wap/jsapi/core.js","a/a_config.js","biz_common/utils/url/parse.js","a/a_utils.js","biz_wap/utils/mmversion.js","pages/utils.js","common/comm_report.js","biz_common/dom/event.js","biz_common/dom/class.js","common/utils.js"],function(e){
"use strict";
var n=e("biz_wap/utils/ajax.js"),t=e("biz_wap/jsapi/core.js"),i=e("a/a_config.js"),a=e("biz_common/utils/url/parse.js"),o=e("a/a_utils.js"),s=e("biz_wap/utils/mmversion.js"),r=e("pages/utils.js"),c=e("common/comm_report.js"),l=e("biz_common/dom/event.js"),d=e("biz_common/dom/class.js"),u=e("common/utils.js"),p=a.getQuery("wcslplayerId");
return function(e){
function f(e,n,i){
if(p){
var a={
__videoTailPlayerId__:p,
action:e,
data:n
};
"function"==typeof i&&(a.callbackId=G+L++,Y[a.callbackId]=i),window.postMessage(a,document.location.protocol+"//mp.weixin.qq.com");
}else"function"!=typeof i&&(i=function(){}),t.invoke(e,n,i);
}
function _(e,n){
"function"==typeof n&&(Y[e]?Y[e].push(n):Y[e]=[n],t.on(e,n));
}
function m(e){
"object"===_typeof(e.data)&&"string"==typeof e.data.hostEnvEvent&&Y[e.data.hostEnvEvent]&&Y[e.data.hostEnvEvent].forEach(function(n){
return n(e.data.res);
});
}
function b(){
return s.cpVersion("7.0.9",1,!0);
}
function y(e){
en=_extends(en,e);
}
function v(){
var e=arguments.length<=0||void 0===arguments[0]?{}:arguments[0];
for(var n in e)e[n]&&(an[n]=e[n]);
}
function w(){
return d.hasClass(tn.panelEl,"has_ad")?1:0;
}
function g(){
return _extends({
ReportWithTailAd:w()
},an);
}
function h(){
f("handleMPPageAction",{
action:"closeAdWebview"
});
}
function P(e){
return b()||en.hasAd&&!e?void(e?en.hidePanelAd&&en.hidePanelAd():en.showTailPanel&&en.showTailPanel(en)):void h();
}
function E(){
return p?U:window.innerWidth===screen.width&&window.innerHeight===screen.height||window.innerWidth===screen.height&&window.innerHeight===screen.width;
}
function T(e){
var n;
return a.join(location.origin+"/mp/authreadtemplate?t=pages/video_tail",(n={
vid:Q.vid,
item_show_type:window.item_show_type,
idx:window.idx,
mid:window.mid,
sn:window.sn,
scene:window.scene,
appmsg_type:window.appmsg_type,
msg_title:window.msg_title,
ct:window.ct,
send_time:window.send_time,
abtest_cookie:window.abtest_cookie,
msg_daily_idx:window.msg_daily_idx,
user_uin:window.user_uin,
__biz:window.biz,
pos_type_list:9,
get_ad_after_video:1
},_defineProperty(n,i.HAS_AD_DATA_QUERY_KEY,e?1:0),_defineProperty(n,"enterid",window.enterid),
_defineProperty(n,"subscene",window.subscene),_defineProperty(n,"oriStatus",Q.ori_status),
_defineProperty(n,"hitBizUin",Q.hit_bizuin),_defineProperty(n,"hitVid",Q.hit_vid),
_defineProperty(n,"sessionid",window.sessionid),_defineProperty(n,"devicetype",window.devicetype),
_defineProperty(n,"playerType",u.getPlayerType()),_defineProperty(n,"hasSubscribed",en.hasSubscribed?1:0),
_defineProperty(n,"continueid",window.continueid+""),_defineProperty(n,"continueseq",1*a.getQuery("continueseq")||1),
n));
}
function j(e){
on=e;
}
function S(e,t,i){
if(!$||i){
var a=T(on)+"&wcslplayerId="+t;
window.__second_open__?n({
url:a,
type:"GET",
f:"html",
success:function(n){
e.setAttribute("src",a),e.contentWindow.document.open("text/html","replace"),e.contentWindow.document.write(n),
e.contentWindow.document.close(),e.contentWindow.history.replaceState(null,null,a);
}
}):e.setAttribute("src",a),F=e,$=!0;
}
}
function A(e){
$||t.invoke("handleMPPageAction",{
action:"createAdWebview",
adUrl:T(e)
},function(e){
return e.err_msg.indexOf("fail")>-1?void o.report115849(40):void($=!0);
});
}
function I(e){
y({
showTailPanel:e.showTailPanel,
hidePanelAd:e.hidePanelAd
}),_("onMPAdWebviewStateChange",function(e){
"appear"===e.state&&(e.forceNoAd&&y({
hasAd:!1
}),P(),en.hasAd&&setTimeout(function(){
en.showAd&&en.showAd();
},10));
});
}
function x(e){
function n(){
o=!0,setTimeout(function(){
return s?void(o=!1):(r+=l,(en.canCreateTailWebview||c>=a-r)&&A(),void n());
},1e3*l);
}
function i(){
t.invoke("handleMPPageAction",{
action:"getMPVideoState"
},function(t){
t.vid===e&&(r=parseInt(t.currentTime,10)>=parseInt(t.duration,10)?0:t.currentTime,
a=t.duration,"play"===t.state&&!o&&n());
});
}
var a=void 0,o=void 0,s=!1,r=0,c=10,l=.5;
t.on("onMPVideoStateChange",function(e){
"play"===e.state?(i(),s=!1):"enterFullScreen"!==e.state&&"exitFullScreen"!==e.state&&(s=!0);
}),i();
}
function W(e){
x(e),t.on("onMPAdWebviewStateChange",function(e){
"destroy"===e.state&&($=!1);
});
}
function B(e){
_("onReceiveMPPageData",function(n){
e&&e(n);
});
}
function z(e,n){
F&&"adWeb"===n?F.contentWindow.postMessage({
hostEnvEvent:"onReceiveMPPageData",
res:{
data:e
}
},document.location.protocol+"//mp.weixin.qq.com"):f("handleMPPageAction",{
action:"sendMPPageData",
data:e,
sendTo:n
});
}
function M(e){
var n=E(),t=void 0;
t=w()?n?184:183:n?181:180,c.report(17149,_extends({
EventType:n?46:47
},g())),e.dataset.scene=t;
}
function k(e){
nn&&(e?(tn.subscribeBtn.style.display="none",tn.profileIcon.style.display="",!Z&&(tn.subscribeSuccess.style.display="")):(tn.subscribeBtn.style.display="",
tn.profileIcon.style.display="none",tn.subscribeSuccess.style.display="none"),Z=e);
}
function C(){
if(nn){
var e=E();
e&&J||!e&&X||(c.report(17149,_extends({
EventType:e?70:71
},g())),e?J=!0:X=!0);
}
}
function D(){
c.report(17149,_extends({
EventType:E()?72:73
},g()));
}
function N(){
return Z;
}
function O(e){
n({
url:"/mp/videochannel_profile_page?action=check_contact&biz_username="+e.userName+"&__biz="+e.biz,
dataType:"json",
success:function(n){
var t=1===n.subscribed;
e.success&&e.success(t);
}
});
}
function V(e){
function n(){
O({
userName:e.userName,
biz:e.biz,
success:function(e){
k(e),C(),e&&z("hasSubscribed","commshareWeb");
}
});
}
tn.accountName.innerHTML=e.nickname,tn.accountAvatar.src=e.headImg,e.subscribed||k(!1),
e.notBindProfileEvt?!function(){
var e=tn.profileBtn;
l.tap(e,function(){
M(e);
});
}():r.go2ProfileEvent({
$container:tn.panelEl,
user_name:e.userName,
beforeGo2Profile:M,
tabType:2
}),nn&&(l.on(tn.subscribeBtn,"tap",function(){
var n=void 0;
D(),n=E()?"186":"185",t.invoke("addContact",{
webtype:"1",
username:e.userName,
scene:n,
scenenote:e.pageUrl||""
},function(e){
e.err_msg.indexOf("ok")>-1&&(k(!0),z("hasSubscribed","commshareWeb"));
});
}),l.bindVisibilityChangeEvt(function(e){
if(e){
var t=3;
n();
for(var i=1;t>=i;i++)setTimeout(n,200*t);
}
}));
}
function R(){
l.tap(r.getId("js_tail_share_button"),function(){
c.report(17149,_extends({
EventType:E()?53:54
},g()));
});
}
function H(e){
tn.panelEl=document.getElementById("js_video_tail_panel_"+e),tn.subscribeBtn=tn.panelEl.getElementsByClassName("js_btn_account_subscription")[0],
tn.profileIcon=tn.panelEl.getElementsByClassName("js_profile_icon")[0],tn.subscribeSuccess=tn.panelEl.getElementsByClassName("js_subscription_success")[0],
tn.accountAvatar=tn.panelEl.getElementsByClassName("account_avatar")[0],tn.accountName=tn.panelEl.getElementsByClassName("account_name")[0],
tn.profileBtn=tn.panelEl.getElementsByClassName("js_go_profile")[0],tn.replayBtn=tn.panelEl.getElementsByClassName("js_replay")[0];
}
function q(e){
if(H(e.vid),!b()||!tn.panelEl)return void(e.fallback&&e.fallback());
e.reportData.PlayerType=1,v(e.reportData),tn.panelEl.style.display="",X=!1;
var n={
Vid:an.VideoId,
BizUin:an.BizUserName,
msgid:an.MsgId,
itemidx:an.Idx,
Type:1,
ClientTime:Date.now(),
Fromid:an.Scene,
SessionId:an.SessionIdStr,
Device:s.isIOS?1:2
};
e.isAppMsg?c.report(12710,_extends({},an,n,{
Step:17,
ClientTime:Date.now()
})):(c.report(17149,_extends({
EventType:65
},an)),c.report(17149,_extends({
EventType:67
},an)),c.report(17149,_extends({
EventType:69
},an)),(!e.subscribed&&!K||!Z&&K)&&C()),K||(V(e),R(),l.tap(tn.replayBtn,function(){
return tn.panelEl.style.display="none",e.replay&&e.replay(),e.isAppMsg?c.report(12710,_extends({},an,n,{
Step:18,
ClientTime:Date.now()
})):c.report(17149,_extends({
EventType:52
},an)),!1;
},!0),K=!0);
}
var U=!1,F=null,Q=e||window.cgiData,G="video_tail_callback_",L=0,Y={};
p&&window.addEventListener("message",function(e){
"object"===_typeof(e.data)&&"string"==typeof e.data.callbackId&&e.data.callbackId.startsWith(G)?(Y[e.data.callbackId]&&Y[e.data.callbackId](e.data.res),
delete Y[e.data.callbackId]):m(e);
});
var K=!1,$=!1,J=!1,X=!1,Z=!0,en={},nn=s.isIOS&&s.cpVersion("7.0.15",1,!0);
nn=nn||s.isAndroid&&s.cpVersion("7.0.17",1,!0);
var tn={
subscribeBtn:null,
profileIcon:null,
subscribeSuccess:null,
panelEl:null,
accountName:null,
accountAvatar:null,
profileBtn:null,
replayBtn:null
},an={
EnterId:parseInt(Date.now()/1e3,10),
ItemShowType:5
};
p&&_("onWcSlPlayerFullscreenChange",function(e){
U=e.state,"string"==typeof e.padding&&(document.body.style.padding=e.padding);
});
var on=!1;
return{
createTailWebview:A,
initEvent4TailWebview:I,
listenAndCreateTailWebview:x,
onReceiveMPPageData:B,
setTailOpts:y,
showTailPanel:P,
sendMPPageData:z,
handleTailWebviewState:W,
closeTailWebview:h,
initProfile:V,
initWebTailPanel:q,
isFullScreen:E,
getSubscribedStatus:N,
reportSubscribeBtnExpose:C,
changeSubscribeStatus:k,
getSubscribedData:O,
supportTailPanel:b,
getReportData:g,
initShareBtnReport:R,
setReportData:v,
setHasAdData4WcSlPlayer:j,
initTailIframe4WcSlPlayer:S,
emitHostEnvEvent4WcSlPlayer:m,
sendMessageToHostEnv:f
};
};
});define("pages/video_plugin/base.js",[],function(){
"use strict";
var t=0,e=function(t,e){
var n=function(){};
n.prototype=e.prototype,t.prototype=new n,t.prototype.constructor=t,t.uber=e.prototype;
},n=function(){
this.player=null;
};
return n.prototype.setPlayer=function(t){
this.player=t;
},n.prototype.setBlockEvt=function(t){
this.player._setBlockPlugin(t,this);
},n.prototype.setUnblockEvt=function(t){
this.player._setBlockPlugin(t,null);
},n.prototype.recv=function(e){
var n=this[e+"Handler"];
if("function"==typeof n){
var o=n.apply(this,arguments);
return"undefined"==typeof o||null===o?t:o;
}
return t;
},{
Class:n,
inherit:e,
BASE_BITSET:t
};
});var _extends=Object.assign||function(e){
for(var t=1;t<arguments.length;t++){
var o=arguments[t];
for(var n in o)Object.prototype.hasOwnProperty.call(o,n)&&(e[n]=o[n]);
}
return e;
};
define("pages_new/common_share/video/player/plugins/auto_next/auto_next_store.js",["biz_wap/jsapi/log.js","pages/utils.js","common/comm_report.js","biz_wap/utils/jsmonitor_report.js"],function(e){
"use strict";
var t=e("biz_wap/jsapi/log.js"),o=e("pages/utils.js"),n=e("common/comm_report.js"),s=e("biz_wap/utils/jsmonitor_report.js");
return{
name:"auto-next-plugin",
namespaced:!0,
state:function(){
return{
autoNextStatus:0
};
},
getters:{
nextVideo:function(e,t,o){
var n=o.extRes;
if(n.related_tag_video&&n.related_tag_video.length)for(var s=0;s<n.related_tag_video.length;s++){
var a=n.related_tag_video[s];
if(1!==a.user_read_status)return{
source:1,
vid:a.vid,
url:a.url,
recInfo:a.rec_info,
title:a.title||"更多精彩视频",
cover:a.cover||"",
headImg:a.head_img_url||"",
bizNickName:a.srcDisplayName||""
};
}
return null;
},
report17149Data:function(e,t,n){
var s=n.cgiData,a=n.extRes;
return{
BizUserName:s.biz,
MsgId:1*s.mid,
Idx:1*s.idx,
EnterId:s.enterid,
VideoId:s.vid,
Scene:s.scene,
Subscene:1*s.subscene,
SessionIdStr:s.sessionid,
ChannelSessionId:s.channel_session_id,
ContinueId:s.continueid+"",
ReloadId:s.reloadid+"",
Device:s.devicetype,
ContinueSource:t.nextVideo&&t.nextVideo.source||0,
MoreVideosInfo:t.nextVideo&&o.getMoreVideoInfo(t.nextVideo.url,t.nextVideo.vid)||"",
VideoRecommendType:a.video_recommend_type||0,
MoreVideoSortId:a.more_video_sort_id||0,
MoreVideosSeq:s.continueseq,
MoreVideoRecInfo:t.nextVideo&&t.nextVideo.recInfo||""
};
}
},
mutations:{
setAutoNextStatus:function(e,t){
e.autoNextStatus=t.value;
}
},
actions:{
cancelAutoNext:function(e,o){
var n=e.commit,s=e.state,a=e.dispatch;
0===s.autoNextStatus?(n("setAutoNextStatus",{
value:4
}),console.log("[AutoNext Plugin] Cancel autonext for reason "+o+" before tips show"),
t.info("cancel autonext for reason "+o+" before tips show")):a("cancelAutoNextWhenTipsShowed",o);
},
resumeAutoNext:function(e){
var o=e.commit,n=e.state;
4===n.autoNextStatus&&(o("setAutoNextStatus",{
value:0
}),console.log("[AutoNext Plugin] Resume autonext"),t.info("resume autonext"));
},
cancelAutoNextWhenTipsShowed:function(e,o){
var n=e.dispatch,a=e.state;
if(1===a.autoNextStatus){
n("hideTips");
var i=function(){
s.setSum(221764,28,1),n("report17149",{
EventType:87,
ContinueBreakReason:o
});
};
3===o?setTimeout(i):i(),console.log("[AutoNext Plugin] Cancel autonext for reason "+o+" when tips showed"),
t.info("cancel autonext for reason "+o+" when tips showed");
}
},
showTips:function(e){
var t=e.dispatch,o=e.commit,n=e.state;
0===n.autoNextStatus&&(o("setAutoNextStatus",{
value:1
}),s.setSum(221764,25,1),t("report17149",{
EventType:86
}));
},
hideTips:function(e){
var t=e.commit,o=e.state;
1===o.autoNextStatus&&t("setAutoNextStatus",{
value:3
});
},
report17149:function(e,t){
var o=e.getters,s=_extends({},o.report17149Data,t);
n.report(17149,s);
}
}
};
});define("pages_new/common_share/video/player/plugins/mid_ad/mid_ad_store.js",[],function(){
"use strict";
return{
name:"mid-ad-plugin",
namespaced:!0,
state:function(){
return{
midAdStatus:0
};
},
mutations:{
setMidAdStatus:function(t,e){
t.midAdStatus=e.value;
}
}
};
});define("pages_new/common_share/video/player/plugins/popup/popup_store.js",[],function(){
"use strict";
function t(t){
var p=Math.floor(t),u=Math.ceil(t);
return t>p&&p+.5>t?p+.5:t>p+.5&&u>t?u:t;
}
return{
name:"popup-plugin",
namespaced:!0,
state:function(){
return{
currentPopupIdx:-1,
popupData:null
};
},
getters:{
currentPopup:function(t){
var p=t.popupData&&t.popupData[t.currentPopupIdx];
return p&&2!==p.status?p:null;
}
},
mutations:{
setCurrentPopupIdx:function(t,p){
t.currentPopupIdx=p.value;
},
setPopupStatus:function(t,p){
var u=p.index||t.currentPopupIdx,e=t.popupData&&t.popupData[u];
e&&(e.status=p.value);
},
setPopupData:function(p,u){
p.popupData=u.value.dots.map(function(p){
var u={},e={};
try{
u=JSON.parse(p.dot);
}catch(n){}
try{
e=JSON.parse(p.position);
}catch(n){}
return{
status:0,
info:u,
id:p.id,
type:p.type,
position:e,
startTime:t(1*p.begin_time),
endTime:t(1*p.end_time)
};
});
}
}
};
});define("pages_new/common_share/video/player/plugins/danmu/danmu_store.js",[],function(){
"use strict";
return{
name:"danmu-plugin",
namespaced:!0,
state:function(){
return{
inputStatus:0,
danmuInfo:null
};
},
mutations:{
setInputStatus:function(n,t){
n.inputStatus=t.value;
},
setDanmuInfo:function(n,t){
n.danmuInfo=t;
}
}
};
});define("pages_new/common_share/video/player/plugins/tail/tail_store.js",[],function(){
"use strict";
return{
name:"tail-plugin",
namespaced:!0,
state:function(){
return{
tailStatus:0
};
},
mutations:{
setTailStatus:function(t,a){
t.tailStatus=a.value;
}
},
actions:{
setLikeStatus:function(t,a){
var e=t.rootState,s=t.commit;
s("SET_PRAISE_STATUS",{
hasPraised:a.hasPraised
},{
root:!0
}),s("SET_PRAISE_NUM",{
praiseNum:e.extRes.appmsgstat.old_like_num+(a.hasPraised?1:-1)
},{
root:!0
});
}
}
};
});define("pages_new/modules/reward/reward_store.js",[],function(){
"use strict";
return{
name:"mp-reward",
namespaced:!0
};
});var _slicedToArray=function(){
function e(e,t){
var n=[],r=!0,m=!1,o=void 0;
try{
for(var a,i=e[Symbol.iterator]();!(r=(a=i.next()).done)&&(n.push(a.value),!t||n.length!==t);r=!0);
}catch(s){
m=!0,o=s;
}finally{
try{
!r&&i["return"]&&i["return"]();
}finally{
if(m)throw o;
}
}
return n;
}
return function(t,n){
if(Array.isArray(t))return t;
if(Symbol.iterator in Object(t))return e(t,n);
throw new TypeError("Invalid attempt to destructure non-iterable instance");
};
}(),_extends=Object.assign||function(e){
for(var t=1;t<arguments.length;t++){
var n=arguments[t];
for(var r in n)Object.prototype.hasOwnProperty.call(n,r)&&(e[r]=n[r]);
}
return e;
};
define("pages_new/modules/comment/comment_store.js",["pages_new/3rd/vue.js","common/keyboard.js","common/utils.js","biz_wap/utils/mmversion.js","biz_wap/utils/jsmonitor_report.js"],function(e){
"use strict";
var t=e("pages_new/3rd/vue.js"),n=e("common/keyboard.js"),r=e("common/utils.js"),m=e("biz_wap/utils/mmversion.js"),o=e("biz_wap/utils/jsmonitor_report.js"),a="http://mmbiz.qpic.cn/mmbiz/a5icZrUmbV8p5jb6RZ8aYfjfS2AVle8URwBt8QIu6XbGewB9wiaWYWkPwq4R7pfdsFibuLkic16UcxDSNYtB8HnC1Q/0";
return{
name:"mp-comment",
namespaced:!0,
state:function(){
return{
writeStatus:0,
myCommentData:null,
myCommentStatus:0,
commentData:null,
commentStatus:0,
commentVersion:function(){
return m.isWechat?m.isInMiniProgram?0:n.canUseKeyboard?2:(m.isIOS||m.isAndroid)&&(m.gtVersion("7.0.8")||r.isNativePage())?2:0:0;
}(),
offset:0,
replyFlag:0,
warningToast:"",
reportData:{
scene:0,
idkey:"",
moreList:27,
repeatList:25,
errList:18,
handleList:26,
addCommentErr:19,
errComment:18,
repeatContent:24,
repeatContentID:23
}
};
},
getters:{
tempKey:function(e,t,n){
return n.cgiData.tempkey||"";
},
commentId:function(e,t,n){
return n.cgiData.comment_id||"";
},
commentEnabled:function(e,t,n){
return n.extRes.comment_enabled||0;
},
commentCount:function(e,t,n){
return n.extRes.comment_count;
},
nickName:function(e,t,n){
return n.extRes.nick_name||"";
},
headImg:function(e,t,n){
return n.extRes.logo_url||a;
},
isFans:function(e,t,n){
return n.extRes.is_fans||0;
},
isFansDays:function(e,t,n){
return n.extRes.is_fans_days||0;
},
onlyFansCanComment:function(e,t,n){
return n.extRes.only_fans_can_comment||0;
},
onlyFansDaysCanComment:function(e,t,n){
return n.extRes.only_fans_days_can_comment||0;
},
canC2cReply:function(e,t,n){
return!!n.extRes.test_flag&&0!==(256&n.extRes.test_flag);
}
},
mutations:{
setCommentVersion:function(e,t){
e.commentVersion=t.value;
},
setWriteStatus:function(e,t){
e.writeStatus=t.status;
},
setMyCommentData:function(e,t){
e.myCommentData=t.data;
},
setMyCommentStatus:function(e,t){
e.myCommentStatus=t.status;
},
setCommentData:function(e,t){
e.commentData=t.data;
},
setCommentLike:function(e,t){
var n=t.type,r=void 0===n?"mine":n,m=t.commentIdx,o=t.replyIdx,a=t.likeStatus,i="mine"===r?e.myCommentData.my_comment:e.commentData.elected_comment;
if("number"==typeof m&&"undefined"==typeof o){
var s=i[m];
s&&s.like_status!==a&&(s.like_status=a,s.like_num+=a?1:-1);
}else if("number"==typeof m&&"number"==typeof o){
var s=i[m],u=s.reply_new.reply_list[o];
u&&u.reply_like_status!==a&&(u.reply_like_status=a,u.reply_like_num+=a?1:-1,s.reply_new=_extends({},s.reply_new));
}
},
setAnimationStatus:function(e,t){
var n=t.type,r=void 0===n?"mine":n,m=t.commentIdx,o=t.replyIdx,a="mine"===r?e.myCommentData.my_comment:e.commentData.elected_comment;
if("number"==typeof m&&"undefined"==typeof o){
var i=a[m];
i&&(i.needAnimation=!1);
}else if("number"==typeof m&&"number"==typeof o){
var i=a[m],s=i.reply_new.reply_list[o];
s&&(s.needAnimation=!1);
}
},
addComment:function(e,n){
var r=n.type,m=void 0===r?"mine":r,o=n.commentItem,a=n.commentIdx,i=n.replyItem,s=n.replyIdx,u="mine"===m?e.myCommentData.my_comment:e.commentData.elected_comment;
if("undefined"!=typeof o)u.unshift(o);else if("number"==typeof a&&"undefined"!=typeof i){
var c=u[a];
c&&(c.reply_new?("number"==typeof s?c.reply_new.reply_list.splice(s+1,0,i):c.reply_new.reply_list.unshift(i),
c.reply_new.reply_total_cnt++,c.reply_new=_extends({},c.reply_new)):t.set(c,"reply_new",{
reply_list:[i],
reply_total_cnt:1
}));
}
},
removeComment:function(e,t){
var n=t.type,r=void 0===n?"mine":n,m=t.commentIdx,o=t.replyIdx,a="mine"===r?e.myCommentData.my_comment:e.commentData.elected_comment;
if("number"==typeof m&&"undefined"==typeof o)a.splice(m,1);else if("number"==typeof m&&"number"==typeof o){
var i=a[m];
i&&(i.reply_new.reply_list.splice(o,1),i.reply_new.reply_total_cnt--,i.reply_new=_extends({},i.reply_new));
}
},
updateCommentReplyInfo:function(e,t){
var n=t.commentIdx,r=t.key,m=t.value;
if("number"==typeof n){
var o=e.commentData.elected_comment[n];
o&&o.reply_new&&r in o.reply_new&&(o.reply_new[r]=m,o.reply_new=_extends({},o.reply_new));
}
},
setCommentStatus:function(e,t){
e.commentStatus=t.status;
},
setOffset:function(e,t){
e.offset=t.value;
},
setReplyFlag:function(e,t){
e.replyFlag=t.flag;
},
setReportData:function(e,t){
e.reportData=t.data;
},
setWarningToast:function(e,t){
e.warningToast=t.content;
}
},
actions:{
myReport:function(e,t){
var n=e.state,r=_slicedToArray(t,2),m=r[0],a=r[1],i=void 0===a?"":a;
if("undefined"!=typeof m)if(n.reportData.idkey)o.setSum(n.reportData.idkey,m,1);else{
var s=new Image,u=Math.random();
s.src="/mp/jsreport?key="+m+"&content="+i+"&r="+u;
}
}
}
};
});define("pages_new/common_share/video/topic/topic_store.js",[],function(){
"use strict";
return{
name:"mp-topic",
namespaced:!0,
state:function(){
return{
reportStatus:[]
};
},
getters:{
list:function(t,e,n){
var r=n.cgiData.topics||[];
return r;
},
reportStatus:function(t){
return t.reportStatus;
},
hasDesc:function(t,e,n){
return!!n.cgiData.msg_desc;
},
canReward:function(t,e,n){
return n.cgiData.is_need_reward;
}
},
mutations:{
REPORT_ITEM:function(t,e){
t.reportStatus[e]=!0;
}
},
actions:{
reportItem:function(t,e){
t.commit("REPORT_ITEM",e);
}
}
};
});