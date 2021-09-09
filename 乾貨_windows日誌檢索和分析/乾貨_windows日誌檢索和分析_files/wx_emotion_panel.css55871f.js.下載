define("pages_new/common_share/video/player/plugins/mid_ad/mid_ad_store.js",[],function(){
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
});define("pages_new/modules/reward/reward_store.js",[],function(){
"use strict";
return{
name:"mp-reward",
namespaced:!0
};
});var _slicedToArray=function(){
function e(e,t){
var n=[],o=!0,r=!1,m=void 0;
try{
for(var a,i=e[Symbol.iterator]();!(o=(a=i.next()).done)&&(n.push(a.value),!t||n.length!==t);o=!0);
}catch(s){
r=!0,m=s;
}finally{
try{
!o&&i["return"]&&i["return"]();
}finally{
if(r)throw m;
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
for(var o in n)Object.prototype.hasOwnProperty.call(n,o)&&(e[o]=n[o]);
}
return e;
};
define("pages_new/modules/comment/comment_store.js",["pages_new/3rd/vue.js","common/keyboard.js","common/utils.js","biz_wap/utils/mmversion.js","biz_wap/utils/jsmonitor_report.js"],function(e){
"use strict";
var t=e("pages_new/3rd/vue.js"),n=e("common/keyboard.js"),o=e("common/utils.js"),r=e("biz_wap/utils/mmversion.js"),m=e("biz_wap/utils/jsmonitor_report.js"),a="http://mmbiz.qpic.cn/mmbiz/a5icZrUmbV8p5jb6RZ8aYfjfS2AVle8URwBt8QIu6XbGewB9wiaWYWkPwq4R7pfdsFibuLkic16UcxDSNYtB8HnC1Q/0";
return{
name:"mp-comment",
namespaced:!0,
state:function(){
return{
isVoiceover:!1,
writeStatus:0,
myCommentData:null,
myCommentStatus:0,
commentData:null,
commentStatus:0,
commentVersion:function(){
return r.isWechat?r.isInMiniProgram?0:n.canUseKeyboard?2:(r.isIOS||r.isAndroid)&&(r.gtVersion("7.0.8")||o.isNativePage())?2:0:0;
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
setIsVoiceover:function(e,t){
e.isVoiceover=t.value;
},
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
var n=t.type,o=void 0===n?"mine":n,r=t.commentIdx,m=t.replyIdx,a=t.likeStatus,i="mine"===o?e.myCommentData.my_comment:e.commentData.elected_comment;
if("number"==typeof r&&"undefined"==typeof m){
var s=i[r];
s&&s.like_status!==a&&(s.like_status=a,s.like_num+=a?1:-1);
}else if("number"==typeof r&&"number"==typeof m){
var s=i[r],u=s.reply_new.reply_list[m];
u&&u.reply_like_status!==a&&(u.reply_like_status=a,u.reply_like_num+=a?1:-1,s.reply_new=_extends({},s.reply_new));
}
},
setAnimationStatus:function(e,t){
var n=t.type,o=void 0===n?"mine":n,r=t.commentIdx,m=t.replyIdx,a="mine"===o?e.myCommentData.my_comment:e.commentData.elected_comment;
if("number"==typeof r&&"undefined"==typeof m){
var i=a[r];
i&&(i.needAnimation=!1);
}else if("number"==typeof r&&"number"==typeof m){
var i=a[r],s=i.reply_new.reply_list[m];
s&&(s.needAnimation=!1);
}
},
addComment:function(e,n){
var o=n.type,r=void 0===o?"mine":o,m=n.commentItem,a=n.commentIdx,i=n.replyItem,s=n.replyIdx,u="mine"===r?e.myCommentData.my_comment:e.commentData.elected_comment;
if("undefined"!=typeof m)u.unshift(m);else if("number"==typeof a&&"undefined"!=typeof i){
var c=u[a];
c&&(c.reply_new?("number"==typeof s?c.reply_new.reply_list.splice(s+1,0,i):c.reply_new.reply_list.unshift(i),
c.reply_new.reply_total_cnt++,c.reply_new=_extends({},c.reply_new)):t.set(c,"reply_new",{
reply_list:[i],
reply_total_cnt:1
}));
}
},
removeComment:function(e,t){
var n=t.type,o=void 0===n?"mine":n,r=t.commentIdx,m=t.replyIdx,a="mine"===o?e.myCommentData.my_comment:e.commentData.elected_comment;
if("number"==typeof r&&"undefined"==typeof m)a.splice(r,1);else if("number"==typeof r&&"number"==typeof m){
var i=a[r];
i&&(i.reply_new.reply_list.splice(m,1),i.reply_new.reply_total_cnt--,i.reply_new=_extends({},i.reply_new));
}
},
updateCommentReplyInfo:function(e,t){
var n=t.commentIdx,o=t.key,r=t.value;
if("number"==typeof n){
var m=e.commentData.elected_comment[n];
m&&m.reply_new&&o in m.reply_new&&(m.reply_new[o]=r,m.reply_new=_extends({},m.reply_new));
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
var n=e.state,o=_slicedToArray(t,2),r=o[0],a=o[1],i=void 0===a?"":a;
if("undefined"!=typeof r)if(n.reportData.idkey)m.setSum(n.reportData.idkey,r,1);else{
var s=new Image,u=Math.random();
s.src="/mp/jsreport?key="+r+"&content="+i+"&r="+u;
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
});define("pages_new/common_share/video/like_and_share/like_and_share_store.js",["pages_new/common_share/video/like_and_share/actions.js","pages_new/common_share/video/like_and_share/mutations.js","biz_wap/jsapi/core.js","biz_wap/utils/mmversion.js","biz_wap/utils/device.js"],function(e){
"use strict";
var s=e("pages_new/common_share/video/like_and_share/actions.js"),a=e("pages_new/common_share/video/like_and_share/mutations.js"),t=e("biz_wap/jsapi/core.js"),i=e("biz_wap/utils/mmversion.js"),n=e("biz_wap/utils/device.js");
return{
name:"mp-like-and-share",
namespaced:!0,
getters:{
hasExtReqDone:function(e,s,a){
var i=a.extRes;
return i.appmsgstat&&t.invoke("handleHaokanAction",{
imgUrl:a.cgiData.round_head_img?a.cgiData.round_head_img:"",
link:a.cgiData.msg_link.html(!1),
desc:a.cgiData.msg_desc||"",
title:a.cgiData.msg_title,
action:"update_recommend_status",
permission:a.cgiData.is_temp_url||a.extRes.appmsgstat.show_like_gray||!a.extRes.appmsgstat.show_like||2!==a.cgiData.appmsg_like_type?0:1,
recommend:a.extRes.appmsgstat.liked?1:0
},function(){}),!!i.appmsgstat;
},
test:function(e,s,a){
return a.extRes;
},
collectShow:function o(e,s,a){
var o=!1;
return(i.isWechat&&(n.os.iphone&&i.getInner()>"17001000"||n.os.android&&i.getInner()>"27001300")||n.os.windows&&i.getInner()>="63010000")&&(o=!0),
o&&a.extRes.share_flag.show;
},
shareShow:function r(e,s,a){
var r=!1;
return n.os.pc?n.os.windows&&i.getInner()>="63010000"&&(r=!0):r=!0,r&&a.extRes.share_flag.show;
}
},
mutations:a,
actions:s
};
});var _extends=Object.assign||function(e){
for(var t=1;t<arguments.length;t++){
var r=arguments[t];
for(var a in r)Object.prototype.hasOwnProperty.call(r,a)&&(e[a]=r[a]);
}
return e;
};
define("pages_new/common_share/video/related_video_list/related_video_list_store.js",["pages/utils.js"],function(e){
"use strict";
function t(e){
var t=Math.floor(e/60),r=e-60*t;
return 10>r&&(r="0"+r),10>t&&(t="0"+t),t+":"+r;
}
var r=e("pages/utils.js");
return{
name:"mp-related-video-list",
namespaced:!0,
getters:{
hasRelatedVideoList:function(e,t,r){
var a=r.extRes;
return!!a.related_tag_video&&!!a.related_tag_video.length&&a.related_tag_video.length>0;
},
list:function(e,a,n){
var o=n.extRes;
return a.hasRelatedVideoList?o.related_tag_video.map(function(e){
var a=_extends({},e,{
album:!1,
formatDuration:t(e.duration),
read_num:r.formatReadNum(e.read_num||e.readcnt)
});
return a.read_num=""===a.read_num?0:a.read_num,a;
}):[];
},
forMpVideoDataBuffer:function(e,t,r){
var a=r.extRes;
return a.related_video_info?a.related_video_info.push_channel_seq||"":"";
}
}
};
});var _extends=Object.assign||function(e){
for(var n=1;n<arguments.length;n++){
var i=arguments[n];
for(var o in i)Object.prototype.hasOwnProperty.call(i,o)&&(e[o]=i[o]);
}
return e;
};
define("pages_new/common_share/video/lifecycle_manager.js",["biz_wap/jsapi/log.js","biz_wap/utils/ajax.js","common/utils.js","biz_wap/jsapi/core.js","biz_wap/utils/device.js","biz_common/utils/cookie.js","biz_wap/utils/mmversion.js","pages_new/modules/utils/url.js","biz_wap/jsapi/leaveReport.js","biz_wap/utils/jsmonitor_report.js","pages_new/common_share/video/report.js"],function(e){
"use strict";
function n(){
return z;
}
function i(e){
z=I&&e;
}
function o(e){
M.setSum(221764,k.isIOS?e:e+1,1),M.send();
}
function t(e){
_({
url:e.replace(/#.*$/,"")+"&action=report",
type:"POST",
timeout:2e3
});
}
function a(e){
"function"==typeof e&&O.push(e);
}
function r(e){
"function"==typeof e&&b.push(e);
}
function c(e){
"function"==typeof e&&C.push(e);
}
function s(){
O.forEach(function(e){
return e();
});
}
function l(){
b.forEach(function(e){
return e(!1);
});
}
function f(e){
C.forEach(function(n){
return n(e);
});
}
function u(e,n){
window.uin=n.uin||window.uin||"",window.key=n.key||window.key||"",window.wxtoken=n.wxtoken||window.wxtoken||"",
window.pass_ticket=n.pass_ticket&&encodeURIComponent(n.pass_ticket.html(!1).html(!1).replace(/\s/g,"+"))||window.pass_ticket||"",
window.__initGlobalData(e,n),window.__initCgiDataConfig(e,n),window.__initCommentConfig(e,n);
}
function p(e){
var n=S.get("appmsg_token");
if(n)window.appmsg_token=n||window.appmsg_token||"",console.info("[Lifecycle Manager] Update Csrf Token By Cookie",window.appmsg_token),
y.info("[Lifecycle Manager] Update Csrf Token By Cookie",window.appmsg_token),"function"==typeof e.success&&e.success();else{
if(o(34),k.isIOS)return void("function"==typeof e.success&&e.success());
"function"==typeof e.error&&e.error();
}
}
function d(e){
r(e.init),a(e.destroy),c(e.getData),"function"==typeof e.init&&e.init(!0);
}
function g(e,n){
z&&n&&!D[n]&&_({
url:e.replace(/scene=\d+/g,"scene=9876").replace(/#.*$/,"")+"&action=preload",
type:"GET",
timeout:2e3,
success:function(i){
try{
D[n]=JSON.parse(i),console.info("[Lifecycle Manager] Preload PageData",n,e,D[n]),
y.info("[Lifecycle Manager] Preload PageData",n,e);
}catch(o){
console.error("[Lifecycle Manager] Parse Preload PageData Failed",n,e,o),y.error("[Lifecycle Manager] Parse Preload PageData Failed",n,e,o.toString());
}
D[n]&&D[n].video_page_info&&"string"==typeof D[n].video_page_info.cover_url&&((new Image).src=D[n].video_page_info.cover_url);
}
});
}
function w(e,n){
if(!E){
if(E=!0,console.info("[Lifecycle Manager] Start to switch to",e),y.info("[Lifecycle Manager] Start to switch to",e),
P.add19735ExtData({
EventType:3
}),L.reportNow(),!z)return void m.loadNewPageKeepingHistoryStackIfSecOpen(e);
if(k.isIOS){
var i=e.match(/__biz=(.*?)&/);
if(!i||i[1]!==window.biz)return void(location.href=e.replace(/#.*$/,"")+"#wechat_redirect");
}
var a=j.getParams(location.href),r=_extends({
ascene:a.ascene,
devicetype:a.devicetype,
version:a.version,
nettype:a.nettype,
lang:a.lang,
pass_ticket:a.pass_ticket
},j.getParams(e)),c=3e3,d=2,g=0,w=null;
document.cookie="appmsg_token=;path=/",s();
var h=function(){
g===d&&(w&&w.base_resp&&0===w.base_resp.ret?(D={},l(),E=!1,t(e),o(30),console.info("[Lifecycle Manager] Finish to switch to",e),
y.info("[Lifecycle Manager] Finish to switch to",e)):m.loadNewPageKeepingHistoryStackIfSecOpen(e));
},S=setTimeout(function(){
o(32),location.href===e?location.reload():m.loadNewPageKeepingHistoryStackIfSecOpen(e);
},c),M=function b(n){
document.removeEventListener("WeixinJSBridgeAuthChanged",b),console.info("[Lifecycle Manager] GetA8Key Success",n.state),
y.info("[Lifecycle Manager] GetA8Key Success",n.state),history.replaceState(null,"",n.fullUrl),
clearTimeout(S),k.isIOS&&(window.__second_open__=G),p({
url:e,
success:function(){
g++,h();
},
error:function(){
m.loadNewPageKeepingHistoryStackIfSecOpen(e);
}
});
};
document.addEventListener("WeixinJSBridgeAuthChanged",M),history.replaceState(null,"",e);
var O=function C(){
k.isAndroid&&document.removeEventListener("WeixinJSBridgeSpaHistoryChanged",C),console.info("[Lifecycle Manager] History Stack Changed"),
y.info("[Lifecycle Manager] History Stack Changed"),k.isIOS&&(G=window.__second_open__),
delete window.__second_open__,v.invoke("doAuthCurrentUrl",{},function(n){
n&&n.err_msg&&-1!==n.err_msg.indexOf(":ok")?(console.info("[Lifecycle Manager] Invoke GetA8Key Success",n),
y.info("[Lifecycle Manager] Invoke GetA8Key Success",JSON.stringify(n))):(console.error("[Lifecycle Manager] Invoke GetA8Key Failed",n),
y.error("[Lifecycle Manager] Invoke GetA8Key Failed",JSON.stringify(n)),clearTimeout(S),
m.loadNewPageKeepingHistoryStackIfSecOpen(e));
});
};
k.isAndroid?document.addEventListener("WeixinJSBridgeSpaHistoryChanged",O):O(),n&&D[n]?(console.info("[Lifecycle Manager] Get Cache PageData",n),
y.info("[Lifecycle Manager] Get Cache PageData",n),w=D[n],u(w,r),f(w),g++,h()):_({
url:e.replace(/scene=\d+/g,"scene=9875").replace(/#.*$/,"")+"&action=preload",
type:"GET",
async:!1,
timeout:2e3,
success:function(n){
try{
w=JSON.parse(n),console.info("[Lifecycle Manager] Get PageData",w),y.info("[Lifecycle Manager] Get PageData");
}catch(i){
console.error("[Lifecycle Manager] Parse PageData Failed",e,i),y.error("[Lifecycle Manager] Parse PageData Failed",e,i.toString());
}
w&&(u(w,r),f(w)),g++,h();
},
error:function(){
m.loadNewPageKeepingHistoryStackIfSecOpen(e);
}
});
}
}
var y=e("biz_wap/jsapi/log.js"),_=e("biz_wap/utils/ajax.js"),m=e("common/utils.js"),v=e("biz_wap/jsapi/core.js"),h=e("biz_wap/utils/device.js"),S=e("biz_common/utils/cookie.js"),k=e("biz_wap/utils/mmversion.js"),j=e("pages_new/modules/utils/url.js"),L=e("biz_wap/jsapi/leaveReport.js"),M=e("biz_wap/utils/jsmonitor_report.js"),P=e("pages_new/common_share/video/report.js"),O=[],b=[],C=[],I=window.top===window&&k.isWechat&&!k.isInMiniProgram&&!window.is_teenager&&(h.os.iphone&&k.gtVersion("8.0.3",1)||h.os.android&&k.gtVersion("8.0.1",1)),z=!1,E=!1,D={},G=void 0;
return I&&k.isIOS&&(console.info("[Lifecycle Manager] Overwrite sys:auth"),y.info("[Lifecycle Manager] Overwrite sys:auth"),
v.on("sys:auth",function(e){
console.info("[Lifecycle Manager] Get sys:auth Event",e),y.info("[Lifecycle Manager] Get sys:auth Event",JSON.stringify(e));
var n=document.createEvent("Events");
n.initEvent("WeixinJSBridgeAuthChanged"),n.state=e.state,n.fullUrl=e.fullUrl,document.dispatchEvent(n);
})),{
isSpaMode:n,
setSpaMode:i,
register:d,
openNewVideoPage:w,
preloadNewVideoPageData:g
};
});function _typeof(e){
return e&&"undefined"!=typeof Symbol&&e.constructor===Symbol?"symbol":typeof e;
}
define("pages_new/modules/utils/url.js",[],function(){
"use strict";
var e=function(e){
var n=[],t={};
if(!e)try{
e=window.top.location,n=e.search.substring(1).split("&");
}catch(o){
e=window.location,n=e.search.substring(1).split("&");
}
"string"==typeof e&&(e=new URL(e),n=e.search.substring(1).split("&"));
for(var r=0;r<n.length;r++){
var i=n[r].split("="),s=decodeURIComponent(i.shift());
"undefined"==typeof t[s]&&(t[s]=decodeURIComponent(i.join("=")));
}
return t;
},n=function(e,n,t){
return"string"!=typeof e?"":(n&&"object"===("undefined"==typeof n?"undefined":_typeof(n))&&Object.keys(n).length&&(e+="?"+Object.keys(n).map(function(e){
return e+"="+encodeURIComponent(n[e]);
}).join("&")),t&&"string"==typeof t&&(e+="#"+t),e);
};
return{
getParams:e,
genUrl:n
};
});;define('widget/wx-widget/wx_emotion_panel.css', [], function(require, exports, module) {
	return ".comment_primary_emotion_list_mobile{padding:8px 0;overflow-y:scroll}.comment_primary_emotion_item{float:left;padding:4px;cursor:pointer;list-style:none}.comment_primary_emotion_item:hover{background-color:#f7f7f7}.comment_primary_emotion{display:block;width:24px;height:24px;background:transparent url(\/mmbizwap\/zh_CN\/htmledition\/images\/icon\/common\/emotion_panel\/icon_emotion_panel.2x55871f.png) no-repeat 0 0;background-size:24px}@media(prefers-color-scheme:dark){.comment_primary_emotion_item:hover{background-color:#202020}}";
});