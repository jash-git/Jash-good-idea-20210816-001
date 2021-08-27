define("appmsg/comment/comment_input/comment_input.html.js",[],function(){
return'<div class="comment_primary_input_area js_wrp" style="display: none">\n  <# if (deviceIsPc) { #>\n    <!-- PC端 -->\n    <div class="comment_primary_input_wrp">\n      <div class="comment_primary_input js_input" contenteditable></div>\n      <div class="comment_primary_input_placeholder js_placeholder"><#=placeholder#></div>\n    </div>\n    <div class="comment_primary_tool js_tool">\n      <button disabled="disabled" class="reset_btn comment_primary_btn js_submit"><#=submitText#></button>\n      <div class="comment_primary_emotion_wrp js_emotion_wrp">\n        <span class="icon_comment_primary_emotion"></span>\n      </div>\n      <!-- 超出字数往comment_primary_counter加comment_primary_counter_warn  -->\n      <span class="comment_primary_counter js_counter" style="display: none">\n        <em class="js_counter_len"></em>\n        /\n        <span><#=length#></span>\n      </span>\n    </div>\n  <# } else { #>\n    <!-- 手机端 -->\n    <div class="discuss_textarea_box">\n      <textarea class="discuss_textarea js_input js_placeholder" placeholder="<#=placeholder#>"></textarea>\n      <div class="emotion_tool">\n        <span class="pic_emotion_switch_wrp js_emotion_wrp">\n          <img class="pic_default" src="<#=iconEmotionSwitch#>" alt="">\n          <img class="pic_active" src="<#=iconEmotionSwitchActive#>" alt="">\n          <img class="pic_default_primary" src="<#=iconEmotionSwitchPrimary#>" alt="">\n          <img class="pic_active_primary" src="<#=iconEmotionSwitchActivePrimary#>" alt="">\n        </span>\n      </div>\n    </div>\n\n    <div class="emotion_panel js_emotion_panel">\n      <span class="emotion_panel_arrow_wrp js_emotion_panel_arrow_wrp">\n        <i class="emotion_panel_arrow arrow_out"></i>\n        <i class="emotion_panel_arrow arrow_in"></i>\n      </span>\n      <div class="emotion_list_wrp js_slide_wrapper"></div>\n      <ul class="emotion_navs js_navbar"></ul>\n    </div>\n\n    <div class="discuss_btn_wrp js_tool">\n      <button disabled="disabled" class="weui-btn weui-btn_primary js_submit">留言</button>\n    </div>\n  <# } #>\n</div>\n';
});define("appmsg/emotion/selection.js",[],function(e,n){
"use strict";
function t(e,n,t){
if(!t&&e===n)return!1;
if(e.compareDocumentPosition){
var o=e.compareDocumentPosition(n);
if(20===o||0===o)return!0;
}else if(e.contains(n))return!0;
return!1;
}
function o(e,n){
var o=n.commonAncestorContainer||n.parentElement&&n.parentElement()||null;
return o?t(e,o,!0):!1;
}
n.getSelection=function(){
return document.selection?document.selection:(window.getSelection||document.getSelection)();
},n.getRange=function(e){
var n=getSelection();
if(!n)return null;
var t=void 0;
return n.getRangeAt&&n.rangeCount?t=n.getRangeAt(0):n.getRangeAt||(t=n.createRange()),
t?e&&o(e,t)?t:e?null:t:null;
},n.setCursorToEnd=function(e){
if(e){
var n=getSelection();
n.extend&&(n.extend(e,e.length),n.collapseToEnd&&n.collapseToEnd());
}
},n.contains=t;
});define("appmsg/comment/comment_dialog/comment_dialog.html.js",[],function(){
return'<# if (deviceIsPc) { #>\n  <!-- PC自己写一个dialog并追加到body -->\n  <div class="discuss_more_pc_dialog_wrp js_comment_dialog_pc" style="display: none;">\n    <div class="discuss_more_pc_dialog">\n      <div class="discuss_more_pc_dialog_hd">\n        <strong class="discuss_more_pc_dialog_title">留言</strong>\n        <button class="discuss_more_pc_dialog_close_btn reset_btn js_close">\n          <i class="weui-icon-close"></i>\n        </button>\n      </div>\n      <div class="discuss_more_pc_dialog_bd js_bd">\n        <div class="js_bd_main">\n          <div class="discuss_media_current js_comment_list"></div> <!-- 留言列表 -->\n          <div class="discuss_more_list_area">\n            <div class="discuss_more_list_title">全部回复</div>\n            <ul class="discuss_more_list js_reply_list"></ul> <!-- 回复列表 -->\n\n            <div class="js_loading" style="display: none;">\n              <div class="weui-loadmore weui-loadmore_default">\n                <i class="weui-primary-loading"></i>\n                <span class="weui-loadmore__tips">正在加载</span>\n              </div>\n            </div>\n\n            <!-- 结束线 -->\n            <div style="display: none;">\n              <div class="weui-loadmore weui-loadmore_default weui-loadmore_line weui-loadmore_dot">\n                <span class="weui-loadmore__tips"></span>\n              </div>\n            </div>\n\n            <div class="js_empty" style="display: none;">\n              <div class="weui-loadmore weui-loadmore_default">\n                <span class="weui-loadmore__tips">暂无回复</span>\n              </div>\n            </div>\n          </div>\n        </div>\n      </div>\n    </div>\n    <div class="weui-mask"></div>\n  </div>\n<# } else { #>\n  <!-- 手机端基于bottom_modal组件 -->\n  <div class="js_bd discuss_more_dialog_content">\n    <div class="discuss_more_dialog_content_bd">\n      <div class="discuss_media_current js_comment_list"></div> <!-- 留言列表 -->\n      <div class="discuss_more_list_area">\n        <div class="discuss_more_list_wrp">\n          <div class="discuss_more_list_title">全部回复</div>\n          <div class="discuss_more_list js_reply_list"></div> <!-- 回复列表 -->\n        </div>\n\n        <div class="js_loading" style="display: none;">\n          <div class="weui-loadmore weui-loadmore_default">\n            <i class="weui-primary-loading"></i>\n            <span class="weui-loadmore__tips">正在加载</span>\n          </div>\n        </div>\n\n        <!-- 结束线 -->\n        <div class="js_end" style="display: none;">\n          <div class="weui-loadmore weui-loadmore_default weui-loadmore_line weui-loadmore_dot">\n            <span class="weui-loadmore__tips"></span>\n          </div>\n        </div>\n\n        <!-- 无回复 -->\n        <div class="js_empty" style="display: none;">\n          <div class="tips_global_primary discuss_more_empty_tips">\n            暂无回复          </div>\n        </div>\n      </div>\n    </div>\n    <div class="discuss_more_dialog_content_ft">\n      <div class="discuss_more_form weui-flex js_reply_btn">\n        <div class="weui-flex__item">\n          <div class="discuss_form_input js_placeholder" role="option"></div>\n        </div>\n        <a class="icon_discuss_emotion js_emotion_btn" role="button" aria-label="表情" title="轻点两下打开表情键盘" href="javascript:;"></a>\n      </div>\n    </div>\n  </div>\n<# } #>\n';
});define("appmsg/comment/comment_dialog/c2c_not_support_dialog.html.js",[],function(){
return'<!-- 不支持c2c回复弹窗，基于bottom_modal组件 -->\n\n<!-- bd部分 -->\n<div class="js_bd discuss_more_guide">\n  <p class="discuss_more_guide_tips">更新微信到最新版本，可以回复他人留言</p>\n  <img class="pic_discuss_more_guide" src="<#= comment_c2c_not_support_img #>" alt="">\n</div>\n\n<!-- ft部分 -->\n<div class="js_ft">\n  <a href="javascript:;" class="weui-btn weui-btn_default js_close">知道了</a>\n  <a href="javascript:;" class="weui-btn weui-btn_primary js_update">去更新</a>\n</div>\n';
});function _classCallCheck(t,o){
if(!(t instanceof o))throw new TypeError("Cannot call a class as a function");
}
var _createClass=function(){
function t(t,o){
for(var e=0;e<o.length;e++){
var i=o[e];
i.enumerable=i.enumerable||!1,i.configurable=!0,"value"in i&&(i.writable=!0),Object.defineProperty(t,i.key,i);
}
}
return function(o,e,i){
return e&&t(o.prototype,e),i&&t(o,i),o;
};
}();
define("appmsg/emotion/emotion_pc.js",["biz_common/utils/emoji_data.js","biz_common/utils/emoji_panel_data.js","biz_common/dom/event.js","appmsg/emotion/emotion.js","common/utils.js","biz_wap/utils/mmversion.js","pages/utils.js","biz_common/tmpl.js","appmsg/emotion/emotion_pc.html.js"],function(t,o,e){
"use strict";
var i=t("biz_common/utils/emoji_data.js"),n=t("biz_common/utils/emoji_panel_data.js"),s=t("biz_common/dom/event.js"),a=t("appmsg/emotion/emotion.js").encode,m=t("common/utils.js"),l=t("biz_wap/utils/mmversion.js"),c=t("pages/utils.js"),r=t("biz_common/tmpl.js"),d=t("appmsg/emotion/emotion_pc.html.js"),h="js_emotion_item",u=m.getInnerHeight(),p=13,v=13,f=25.5,j=function(){
function t(o){
_classCallCheck(this,t),this.edata=[],this.emojiText={},this.isShow=!1,this.onSelect=o.onSelect,
this.initEmotionData();
var e=document.createElement("div");
e.innerHTML=r.tmpl(d,{
list:this.edata
},!1);
var i=c.qs(".js_emotion_panel",e);
document.body.appendChild(i),this.dom={
emotionSwitch:o.emotionSwitch,
emotionPanel:i,
emotionList:c.qs(".js_emotion_list",i),
input:o.input,
submit:o.submit,
tool:o.tool
},this.bindEvent();
}
return _createClass(t,[{
key:"initEmotionData",
value:function(){
var t=this,o=[];
n.forEach(function(t,e){
i.some(function(i){
return i.id===t?(o[e]=i,!0):!1;
});
});
for(var e=0;v>e;e++)for(var s=0;p>s;s++){
var a=e*p+s;
o[a]&&this.edata.push({
name:o[a].style,
title:o[a].emoji?o[a].emoji:o[a].cn,
bp:"background-position: 0 -"+a*f+"px;",
id:o[a].id
});
}
o.forEach(function(o){
t.emojiText[o.style]=o.emoji||o.cn;
});
}
},{
key:"bindEvent",
value:function(){
var t=this;
s.on(window,"resize",this.emotionPanelMove),s.tap(this.dom.emotionSwitch,function(){
t[t.isShow?"hide":"show"]();
}),s.tap(this.dom.emotionList,function(o){
for(var e=o.target;e&&e!==t.dom.emotionList&&!e.classList.contains(h);)e=e.parentNode;
e.classList.contains(h)&&"function"==typeof t.onSelect&&t.onSelect(t.edata[e.dataset.index]);
});
}
},{
key:"show",
value:function(){
this.isShow=!0;
var t=this.dom.emotionPanel;
t.style.display="",this.zoomEmotionPanel();
var o=t.getBoundingClientRect();
o.top+o.height>=u&&window.scrollTo(0,window.scrollY+o.height);
}
},{
key:"hide",
value:function(){
this.isShow=!1,this.dom.emotionPanel.style.display="none";
}
},{
key:"zoomEmotionPanel",
value:function(){
var t=this.dom.emotionPanel,o=window.getComputedStyle(c.qs(".rich_media_tool")).zoom,e=this.dom.tool.getBoundingClientRect();
t.style.left=e.right*o+"px",t.style.transform="translateX(-100%)",l.isWindows?t.style.top=window.scrollY+e.top*o+e.height*o+"px":l.isMac&&(t.style.top=(window.scrollY+e.top+e.height)*o+"px");
}
},{
key:"emotionPanelMove",
value:function(){
this.isShow&&this.zoomEmotionPanel();
}
},{
key:"textFilter",
value:function(t){
var o=document.createElement("div");
o.innerHTML=t;
for(var e="",i="",n=[],s=void 0,a=0;a<o.childNodes.length;a++){
var m=o.childNodes[a];
1===m.nodeType&&("IMG"===m.nodeName.toUpperCase()||"I"===m.nodeName.toUpperCase())&&(i=m.getAttribute("class"),
i&&(n=i.split(" "),n.length>1&&"icon_emotion_single"===n[0]&&(e=this.emojiText[n[1]],
s=document.createTextNode(e),o.replaceChild(s,m))));
}
return o.innerHTML.replace(/<br.*?>/gi,"\n").replace(/<.*?>/g,"");
}
}]),t;
}();
e.exports={
Emotion:j,
encode:a
};
});define("appmsg/comment/comment_list/item.html.js",[],function(){
return'<div class="discuss_media js_item <# if (itemType === \'reply\') { #> js_reply_item <# } else { #> js_comment_main <# } #>\n  <# if (!item.is_from_author) { #> discuss_media_user<# } #>\n  <# if (canC2CReply || (!canC2CReply && itemType === \'comment\' && item.is_from_me == 1)) { #> js_can_reply<# } #>\n  <# if (item.needAnimation) { #> discuss_new_show<# } #>\n  "\n\n  <# if (isOversize) { #> style="display: none;" <# } #>\n\n  <# if (itemType === \'comment\') { #>\n    data-my-id="<#=item.my_id#>"\n    data-content-id="<#=item.content_id#>"\n  <# } else { #>\n    data-my-id="<#=my_id#>"\n    data-content-id="<#=content_id#>"\n    data-reply-id="<#=item.reply_id#>"\n  <# } #>\n>\n  <div class="discuss_hd">\n    <img alt="" class="discuss_user_avatar" src="<#=item.logo_url#>">\n  </div>\n  <div class="discuss_bd">\n    <div class="discuss_overview weui-flex weui-flex_align-center">\n      <div class="weui-flex__item discuss_user_info <# if (item.is_from_author) { #> discuss_author_info <# } #>" id="js_discuss_user_info_<# if (itemType === \'comment\') { #><#=item.content_id#><# } else { #><#=content_id#>_<#=item.reply_id#><# } #>"\n        role="option"\n        aria-labelledby="\n        js_discuss_user_info_<# if (itemType === \'comment\') { #><#=item.content_id#><# } else { #><#=content_id#>_<#=item.reply_id#><# } #>\n        js_a11y_comma\n        js_discuss_message_<# if (itemType === \'comment\') { #><#=item.content_id#><# } else { #><#=content_id#>_<#=item.reply_id#><# } #>\n        ">\n        <div class="discuss_user_nickname"><#=item.nick_name#></div>\n        <# if (item.is_from_friend == 1) { #><span class="discuss_relation_tips"> (朋友)</span><# } #>\n        <# if (item.is_from_author) { #><span class="discuss_relation_tips"> (作者)</span><# } #>\n        <# if (typeof item.is_top === \'number\' && item.is_top == 1) { #><span class="icon_appmsg_tag">置顶</span><# } #>\n        <# if (!(type === \'mine\' && itemType === \'reply\' && canC2CReply) && deviceIsPc && !(item.is_elected == 1 || item.reply_is_elected == 1)) { #><span class="tips_global_primary">未精选</span><# } #>\n      </div>\n\n      <# if (!isWxWork) { #>\n        <# if (deviceIsPc) { #>\n          <!-- pc留言操作-->\n          <div class="discuss_opr discuss_opr_pc">\n            <# if (supportReply && (canC2CReply || (!canC2CReply && itemType === \'comment\' && item.is_from_me == 1))) { #>\n              <!-- 留言 输入框聚焦的时候discuss_opr_meta加commenting-->\n              <span title="回复" class="discuss_opr_meta discuss_opr_meta_comment">\n                <button class="sns_opr_btn sns_comment_btn js_<#=itemType#>_reply_pc"></button>\n              </span>\n            <# } #>\n\n            <!-- 更多 展开的时候discuss_opr_meta加openning -->\n            <span title="更多操作" class="discuss_opr_meta discuss_opr_meta_more">\n              <button class="sns_opr_btn sns_more_btn js_dropdown"></button>\n              <div class="discuss_dropdown <# if (type === \'mine\') { #>discuss_dropdown_pos_top_right<# } else { #>discuss_dropdown_pos_top_center<# } #>">\n                <# if (item.is_from_me == 1) { #>\n                  <div class="discuss_dropdown_item js_<#=itemType#>_del">删除</div>\n                <# } #>\n                <div class="discuss_dropdown_item js_<#=itemType#>_complain">投诉</div>\n              </div>\n            </span>\n\n            <# if (!(type === \'mine\' && itemType === \'reply\' && canC2CReply) && (item.is_elected == 1 || item.reply_is_elected == 1)) { #>\n              <span title="<# if ((itemType === \'comment\' && item.like_status == 1) || (itemType === \'reply\' && item.reply_like_status == 1)) { #>取消点赞<# } else { #>点赞<# } #>" class="discuss_opr_meta js_<#=itemType#>_praise <# if ((itemType === \'comment\' && item.like_status == 1) || (itemType === \'reply\' && item.reply_like_status == 1)) { #>praised<# } #>">\n                <button class="sns_opr_btn sns_praise_btn">\n                  <# if (itemType === \'comment\' && item.like_num_format !== 0) { #>\n                    <span class="sns_opr_num sns_opr_gap praise_num"><#=item.like_num_format#></span>\n                  <# } else if (itemType === \'reply\' && item.reply_like_num_format !== 0) { #>\n                    <span class="sns_opr_num sns_opr_gap praise_num"><#=item.reply_like_num_format#></span>\n                  <# } else { #>\n                    <span class="sns_opr_num sns_opr_gap praise_num"></span>\n                  <# } #>\n                </button>\n              </span>\n            <# } #>\n          </div>\n        <# } else { #>\n          <!-- 移动端留言操作-->\n          <div class="discuss_opr">\n            <# if (item.is_from_me == 1) { #>\n              <a role="button" class="weui-wa-hotarea_before discuss_opr_meta discuss_del js_<#=itemType#>_del">删除</a>\n            <# } #>\n\n            <# if (supportReply && (canC2CReply || (!canC2CReply && itemType === \'comment\' && item.is_from_me == 1))) { #>\n              <a role="button" class="weui-wa-hotarea_before discuss_opr_meta js_reply_btn js_can_reply" data-type="<#=itemType#>">回复</a>\n            <# } #>\n\n            <# if (!(type === \'mine\' && itemType === \'reply\' && canC2CReply)) { #>\n              <# if (item.is_elected == 1 || item.reply_is_elected == 1) { #>\n                <span class="discuss_opr_meta js_<#=itemType#>_praise <# if ((itemType === \'comment\' && item.like_status == 1) || (itemType === \'reply\' && item.reply_like_status == 1)) { #>praised<# } #>">\n                  <button class="weui-wa-hotarea sns_opr_btn sns_praise_btn">\n                    <span class="aria_hidden_abs">赞</span>\n                    <# if (itemType === \'comment\' && item.like_num_format !== 0) { #>\n                      <span class="sns_opr_num sns_opr_gap praise_num"><#=item.like_num_format#></span>\n                    <# } else if (itemType === \'reply\' && item.reply_like_num_format !== 0) { #>\n                      <span class="sns_opr_num sns_opr_gap praise_num"><#=item.reply_like_num_format#></span>\n                    <# } else { #>\n                      <span class="sns_opr_num sns_opr_gap praise_num"></span>\n                    <# } #>\n                  </button>\n                </span>\n              <# } else { #>\n                <span class="discuss_opr_meta">未精选</span>\n              <# } #>\n            <# } #>\n          </div>\n        <# } #>\n      <# } #>\n    </div>\n\n    <div aria-hidden="true" class="discuss_message" id="js_discuss_message_<# if (itemType === \'comment\') { #><#=item.content_id#><# } else { #><#=content_id#>_<#=item.reply_id#><# } #>">\n      <span class="discuss_status"><#=item.status#></span>\n      <div class="wx_folder js_folder_area">\n        <# if (type === \'reply\' && item.to_nick_name) { #>\n          <div class="discuss_message_content wx_folder_normal js_content">回复 <strong class="discuss_message_reply_nickname"><#=item.to_nick_name#></strong>：<#=item.content#></div>\n        <# } else { #>\n          <div class="discuss_message_content wx_folder_normal js_content"><#=item.content#></div>\n        <# } #>\n        <# if (type === \'comment\') { #>\n          <div aria-hidden="true" class="discuss_message_content wx_folder_fake js_fake_content"><#=item.content#></div>\n\n          <!-- 当normal和fake不等高的时候显示展开按钮 -->\n          <button aria-hidden="true" class="wx_folder_btn reset_btn js_folder" type="button" style="display: none;">展开</button>\n        <# } #>\n      </div>\n    </div>\n\n    <!-- 预览上次回复内容 -->\n    <!-- <# if (item.to_nick_name && item.to_content) { #>\n      <div class="discuss_reply_primary">\n        <div class="discuss_reply_primary_inner">\n          <# if (item.to_reply_del_flag === 0) { #>\n            <strong class="discuss_reply_nickname"><#=item.to_nick_name#>: </strong>\n            <p class="discuss_reply_content js_to_content"><#=item.to_content#></p>\n          <# } else { #>\n            <p class="discuss_reply_content">回复已删除</p>\n          <# } #>\n        </div>\n      </div>\n    <# } #> -->\n\n    <# if (type === \'comment\' || type === \'reply\') { #>\n      <div class="discuss_extra_info discuss_extra_info_primary">\n        <div class="discuss_extra_info_meta"><#=item.time#></div>\n        <# if (type === \'reply\' && !item.is_from_author && item.author_like_status) { #>\n          <div class="discuss_extra_info_meta">作者赞过</div>\n        <# } #>\n      </div>\n    <# } #>\n\n\n    <!-- pc回复留言输入框 -->\n    <div class="discuss_reply_form_area js_input_pc"></div>\n  </div>\n</div>\n';
});define("appmsg/comment/comment_list/comment_item.html.js",[],function(){
return'<li class="js_comment_item discuss_item cid<# if (item.is_from_me == 1) { #><#=item.my_id#><# } else { #><#=item.content_id#><# } #>"\n  id="cid<# if (item.is_from_me == 1) { #><#=item.my_id#><# } else { #><#=item.content_id#><# } #>"\n  data-elected="<#=item.report_elected#>"\n  data-friend="<#=item.report_friend#>"\n  data-my-id="<#=item.my_id#>"\n  data-content-id="<#=item.content_id#>"\n\n  <# if (isOversize) { #> style="display: none;" <# } #>\n>\n  <mp-comment-item></mp-comment-item> <!-- 这里只是一个占位符而已（即虚拟节点），最终会被替换成留言节点DOM（./item.html），由于是全匹配，所以不要随便改这个虚拟节点 -->\n\n  <# if (type !== \'comment\') { #>\n    <div class="discuss_reply_area">\n      <div class="discuss_reply js_reply_list">\n        <# if (item.reply_new && item.reply_new.reply_list && item.reply_new.reply_list.length > 0) { #>\n          <mp-reply-list></mp-reply-list> <!-- 这里只是一个占位符而已（即虚拟节点），最终会被替换成多个回复节点DOM（./item.html），由于是全匹配，所以不要随便改这个虚拟节点 -->\n        <# } #>\n      </div>\n\n      <# if (type !== \'mine\') { #>\n        <div class="discuss_extra_info js_more_reply" <# if (item.reply_new.reply_total_cnt === 0 || item.reply_new.reply_total_cnt === item.reply_new.reply_list.length) { #> style="display: none;" <# } #>>\n          <a href="javascript:;" role="button" class="dicuss_reply_more js_extend_comment weui-wa-hotarea_before">共<span class="js_reply_length"><#=item.reply_new.reply_total_cnt#></span>条回复</a>\n        </div>\n      <# } #>\n    </div>\n  <# } #>\n</li>\n';
});define("common/actionSheet.js",["biz_wap/ui/weui.js","biz_wap/jsapi/core.js","common/navShadow.js","common/keyboard.js","biz_wap/utils/mmversion.js"],function(n){
"use strict";
n("biz_wap/ui/weui.js");
var o=n("biz_wap/jsapi/core.js"),i=n("common/navShadow.js"),e=n("common/keyboard.js"),t=n("biz_wap/utils/mmversion.js"),c=!e.onlyUseH5Keyboard||t.isAndroid,a=function(n){
var o=window.weui.actionSheet(n.buttons,[{
label:"取消",
onClick:function(){
"function"==typeof n.onCancel&&n.onCancel();
}
}],{
className:"weui-pop-zindex-primary",
onClose:function(){
i.hide(),"function"==typeof n.onClose&&n.onClose();
},
onClickMask:function(){
"function"==typeof n.onCancel&&n.onCancel();
}
});
i.show({
onClick:function(){
o.hide();
}
});
};
return{
show:function(n){
if(!c)return void a(n);
var i={};
o.invoke("handleMPPageAction",{
action:"showActionSheet",
buttons:n.buttons.map(function(n,o){
var e=""+o;
return i[e]=n.onClick,{
id:e,
label:n.label
};
})
},function(o){
/:ok$/.test(o.err_msg)?"function"==typeof i[o.id]&&i[o.id]():/:canceled$/.test(o.err_msg)?"function"==typeof n.onCancel&&n.onCancel():"action isn't supported"===o.err_desc||"action not support"===o.err_desc?a(n):"function"==typeof n.onFail&&n.onFail(o.err_msg);
});
}
};
});define("appmsg/comment/comment_write_dialog/comment_write_dialog.html.js",[],function(){
return'<div class="js_bd comment_reply_context">\n  <# if (type !== \'comment\') { #>\n    <div class="comment_reply_mod_wrp" role="option">\n      <div class="comment_reply_mod js_reply_to"></div>\n    </div>\n  <# } #>\n\n  <!-- 实际编辑用的textarea -->\n  <textarea placeholder="<#=placeholder#>" class="weui-textarea comment_textarea js_input"></textarea>\n  <!-- 以下textarea是仅用于占位用的，为了防止focus时页面抖动，会在focus的瞬间让上面的textarea高度设为0并显示下面的textarea占位，300ms后再隐藏下面的textarea并显示实际的textarea -->\n  <textarea placeholder="<#=placeholder#>" class="weui-textarea comment_textarea js_placeholder" style="flex: 1; display: none;" readonly></textarea>\n\n  <div class="discuss_toolbar js_toolbar">\n    <a role="button" class="icon_discuss_emotion js_emotion_btn" href="javascript:;">表情</a>\n    <span class="js_input_tips comment_write_counter"></span>\n  </div>\n\n  <!-- <div style="display: none;">\n    <div class="weui-mask_transparent"></div>\n    <div class="weui-toast">\n      <i class="weui-icon-success-no-circle weui-icon_toast"></i>\n      <p class="weui-toast__content">发送中</p>\n    </div>\n  </div> -->\n</div>\n';
});var _extends=Object.assign||function(t){
for(var e=1;e<arguments.length;e++){
var i=arguments[e];
for(var n in i)Object.prototype.hasOwnProperty.call(i,n)&&(t[n]=i[n]);
}
return t;
};
define("pages/bottom_input_bar.js",["biz_wap/zepto/zepto.js","page/pages/bottom_input_bar.css","biz_wap/jsapi/log.js","biz_wap/jsapi/core.js","biz_common/utils/emoji_panel_data.js","biz_common/utils/emoji_data.js","biz_wap/utils/mmversion.js","biz_wap/utils/device.js","biz_common/dom/event.js","appmsg/set_font_size.js"],function(require,exports,module,alert){
"use strict";
function BottomInputBar(t){
this.opt={
placeholder:"",
limit:0
},this.opt=_extends(this.opt,t),this.state={
inChooseEmoji:!1,
listener:{},
limit:this.opt.limit,
show:!1,
keyboardHeight:0,
panelHeight:0,
androidTriggeringEmoji:!1,
androidShowingKeybroad:!1,
androidOriWinInnerHeight:window.innerHeight,
androidMinWinInnerHeight:window.innerHeight,
showEmotionFirst:!1
},this.__isComposition=!1,this.__mount(),this.__bindEvent();
}
require("biz_wap/zepto/zepto.js"),require("page/pages/bottom_input_bar.css");
var Log=require("biz_wap/jsapi/log.js"),JSAPI=require("biz_wap/jsapi/core.js"),panelData=require("biz_common/utils/emoji_panel_data.js"),emojiData=require("biz_common/utils/emoji_data.js"),mmversion=require("biz_wap/utils/mmversion.js"),Device=require("biz_wap/utils/device.js"),DomEvent=require("biz_common/dom/event.js"),fontSize=require("appmsg/set_font_size.js"),getEmojiText=function getEmojiText(emoji){
for(var i=0;i<emojiData.length;i++){
var e=emojiData[i];
switch(emoji){
case e.cn:
return e.emoji||e.cn;

case e.hk:
return e.emoji||e.hk;

case e.us:
return e.emoji||e.us;

case e.emoji:
return e.emoji;

case e.code:
return e.emoji||e.cn;

default:
if(!mmversion.isIOS&&e.code.startsWith("\\ue"))try{
var c=eval("'"+e.code+"'");
if(emoji===c)return e.emoji||e.cn;
}catch(err){}
}
}
return"";
},getRealHeightOfIOSNativePanel=function(t,e){
JSAPI.invoke("handleDeviceInfo",{
action:"getUIParams"
},function(i){
var n=t;
i.isShowBottomBar&&(n-=i.bottomBarHeight),n=Math.max(n,0),"function"==typeof e&&e(n);
});
},androidNavigationBarHeight=0;
mmversion.isAndroid&&!function(){
var t=function(){
JSAPI.invoke("handleMPPageAction",{
action:"getNavigationBarHeight"
},function(t){
androidNavigationBarHeight=t.height||0;
});
};
t(),document.addEventListener("visibilitychange",function(){
!document.hidden&&t();
});
}();
var tpl='<div class="comment__push__container"><div class="js_bottom_input_mask comment__push__mask" style="display: none;"></div><div class="js_bottom_input_wrapper comment__push" style="opacity: 0;"><div class="comment__push__inner"><div class="comment__push__input_wrp"><div class="js_bottom_input_faker comment__push__input__faker"></div><textarea class="js_bottom_input comment__push__input"></textarea><div class="js_bottom_input_counter comment__push__input__counter comment__push__input__counter_warn" style="display: none;"></div></div></div><div class="comment__push__extend"><a href="javascript:;" class="js_bottom_input_emoji comment__push__btn comment__push__emoji weui-wa-hotarea">表情</a><a href="javascript:;" class="js_bottom_input_submit comment__push__btn comment__push__send weui-wa-hotarea">发送</a></div></div></div>';
return BottomInputBar.prototype.__mount=function(){
this.$el=$(tpl),mmversion.isAndroid&&fontSize.keepNormalFontSizeForAndroid(this.$el[0]),
this.inputEle=this.$el.find(".js_bottom_input")[0],this.$mask=this.$el.find(".js_bottom_input_mask"),
this.$inputWrapper=this.$el.find(".js_bottom_input_wrapper"),0!==this.state.limit&&this.inputEle.setAttribute("maxlength",this.state.limit),
this.inputEle.setAttribute("placeholder",this.__filterContent(this.opt.placeholder)),
mmversion.isIOS||this.__initEmojiPanel(),document.body.append(this.$el[0]);
},BottomInputBar.prototype.__bindEvent=function(){
var t=this,e=this.$el.find(".js_bottom_input_submit")[0],i=this.$el.find(".js_bottom_input_emoji")[0];
DomEvent.tap(this.$inputWrapper[0],function(n){
var o=n.target;
o!==t.inputEle&&o!==e&&o!==i&&n.preventDefault();
}),DomEvent.tap(this.$mask[0],function(e){
console.log("hide[mask tap]"),Log.info("hide[mask tap]"),t.hide(),e.preventDefault();
}),DomEvent.on(this.$mask[0],"touchmove",function(e){
console.log("hide[mask touchmove]"),Log.info("hide[mask touchmove]"),t.hide(),e.preventDefault();
}),DomEvent.tap(this.inputEle,function(e){
t.state.inChooseEmoji&&(t.__triggerEmojiPanel(),e.preventDefault());
}),DomEvent.on(this.inputEle,"focus",function(){
t.__emit("focus");
}),DomEvent.on(this.inputEle,"compositionstart",function(){
t.__isComposition=!0;
}),DomEvent.on(this.inputEle,"compositionend",function(){
t.__isComposition=!1,t.__emit("input",{
data:t.getContent(),
inputType:"setContent"
});
}),DomEvent.on(this.inputEle,"blur",function(){
mmversion.isIOS&&!t.state.inChooseEmoji&&(console.log("hide[input blur]"),Log.info("hide[input blur]"),
t.hide()),t.__emit("blur");
}),DomEvent.on(this.inputEle,"input",function(e){
t.__emit("input",{
data:e.target.value,
inputType:"inputContent"
});
}),DomEvent.on(e,mmversion.isIOS?"tap":"click",function(e){
t.__onSend(),e.preventDefault();
}),DomEvent.on(i,mmversion.isIOS?"tap":"click",function(e){
t.__triggerEmojiPanel(),e.preventDefault();
}),window.addEventListener("resize",function(){
return t.__onResize();
}),window.addEventListener("orientationchange",function(){
t.state.show&&"showing"!==t.state.show&&(console.log("hide[orientationchange]"),
Log.info("hide[orientationchange]"),t.hide());
}),mmversion.isIOS&&window.addEventListener("scroll",function(){
t.state.show&&"showing"!==t.state.show&&(console.log("hide[scroll]"),Log.info("hide[scroll]"),
t.hide());
}),this.__bindAppEvent();
},BottomInputBar.prototype.__bindAppEvent=function(){
var t=this;
mmversion.isIOS&&(JSAPI.on("onGetKeyboardHeight",function(e){
e.height&&"none"!==t.$inputWrapper.css("transform")&&(clearTimeout(t.__failToShowChecker),
getRealHeightOfIOSNativePanel(e.height,function(e){
if(t.state.keyboardHeight=e,t.state.show){
t.state.show=!0;
var i="";
t.showEmotionFirst?(t.showEmotionFirst=!1,i="translate3d(0, "+(e-t.state.panelHeight)+"px, 0)"):i="translate3d(0, 0, 0)",
t.$inputWrapper.css({
opacity:1,
transition:"",
bottom:e,
transform:i
});
}
}));
}),JSAPI.on("onGetSmiley",function(e){
if("[DELETE_EMOTION]"===e.smiley)return void t.delContent();
if("[DONE_EMOTION]"===e.smiley)return console.log("hide[onGetSmiley]"),Log.info("hide[onGetSmiley]"),
void t.hide("DONE_EMOTION");
var i=getEmojiText(e.smiley);
i&&t.insertContent(i);
}));
},BottomInputBar.prototype.__emit=function(t){
if("string"!=typeof t)return void console.error("[bottomInputBar] event must be a string");
if("input"===t&&this.__onInput(),"function"==typeof this.state.listener[t]){
for(var e,i=arguments.length,n=Array(i>1?i-1:0),o=1;i>o;o++)n[o-1]=arguments[o];
(e=this.state.listener)[t].apply(e,n);
}
},BottomInputBar.prototype.__onSend=function(){
var t=this.__filterContent(this.getContent());
t=t.replace(/\n/g," "),this.__emit("submit",t),console.log("hide[submit]"),Log.info("hide[submit]"),
this.hide(),this.clear();
},BottomInputBar.prototype.__onResize=function(){
this.state.androidTriggeringEmoji?(this.state.androidTriggeringEmoji=!1,this.state.keyboardHeight=Math.max(window.innerHeight-this.state.keyboardHeight,0),
this.$el.find(".js_bottom_input_emoji_panel").css({
height:this.state.keyboardHeight
}),this.$inputWrapper.css({
opacity:1,
bottom:this.state.keyboardHeight
})):this.state.androidShowingKeybroad?(clearTimeout(this.__failToShowChecker),this.$inputWrapper.css({
opacity:1,
bottom:0,
left:-90===window.orientation?androidNavigationBarHeight:0,
right:90===window.orientation?androidNavigationBarHeight:0
}),this.state.show=!0,this.state.androidShowingKeybroad=!1,this.state.androidMinWinInnerHeight=window.innerHeight,
this.__emit("show")):mmversion.isIOS?(console.log("hide[resize]"),Log.info("hide[resize]"),
this.hide()):this.state.show&&(window.innerHeight>this.state.androidOriWinInnerHeight-10?(console.log("hide[resize]"),
Log.info("hide[resize]"),this.hide()):(this.state.androidMinWinInnerHeight>window.innerHeight&&(this.state.androidMinWinInnerHeight=window.innerHeight),
this.$inputWrapper.css({
bottom:window.innerHeight-this.state.androidMinWinInnerHeight
})));
},BottomInputBar.prototype.__triggerEmojiPanel=function(){
var t=this;
if(this.state.inChooseEmoji=!this.state.inChooseEmoji,mmversion.isIOS)if(this.state.inChooseEmoji)this.$el.find(".js_bottom_input_emoji").removeClass("comment__push__emoji").addClass("comment__push__keyboard"),
this.inputEle.blur(),JSAPI.invoke("showSmileyPanel",{
hidden:!1,
duration:.01
},function(e){
getRealHeightOfIOSNativePanel(e.height,function(e){
t.state.panelHeight=e;
var i=parseFloat(t.$inputWrapper.css("bottom")),n=i-e;
t.$inputWrapper.css("transform","translate3d(0, "+n+"px, 0)"),t.__emit("showEmotionPanel",e);
});
});else{
this.$el.find(".js_bottom_input_emoji").removeClass("comment__push__keyboard").addClass("comment__push__emoji"),
JSAPI.invoke("showSmileyPanel",{
hidden:!0
},function(){});
var e=this.$inputWrapper.css("bottom"),i=this.$inputWrapper.css("transform"),n=(window.innerHeight-this.state.keyboardHeight)/2-1;
Device.os.getNumVersion()<13&&(this.state.show="showing",n=(window.innerHeight+this.state.keyboardHeight-this.$inputWrapper.offset().height)/2),
this.$inputWrapper.css({
opacity:0,
transition:"none",
bottom:n,
transform:"translate3d(0, 0, 0)"
}),this.inputEle.focus(),this.$inputWrapper.css({
bottom:e,
transform:i
}),setTimeout(function(){
t.$inputWrapper.css({
opacity:1,
transition:"",
bottom:t.state.keyboardHeight,
transform:"translate3d(0, 0, 0)"
});
}),this.__emit("hideEmotionPanel");
}else this.state.androidTriggeringEmoji=!0,this.state.keyboardHeight=window.innerHeight,
this.state.inChooseEmoji?(this.$el.find(".js_bottom_input_emoji").removeClass("comment__push__emoji").addClass("comment__push__keyboard"),
this.inputEle.blur(),JSAPI.invoke("handleDeviceInfo",{
action:"hideKeyBoard"
},function(){}),setTimeout(function(){
var e=t.$el.find(".js_bottom_input_emoji_panel");
if(e.css("display",""),t.showEmotionFirst){
t.showEmotionFirst=!1;
var i=e.height();
t.state.keyboardHeight=window.innerHeight-i,t.$inputWrapper.css({
bottom:i
});
}
},200)):(this.$el.find(".js_bottom_input_emoji").removeClass("comment__push__keyboard").addClass("comment__push__emoji"),
this.$el.find(".js_bottom_input_emoji_panel").css("display","none"),this.inputEle.focus());
},BottomInputBar.prototype.__onInput=function(){
var t=this.__filterContent(this.getContent());
return this.__isComposition?void $(".js_bottom_input_faker").html(t.replace(/\n/g,"<br/>")):void this.setInputValue(t);
},BottomInputBar.prototype.__filterContent=function(t){
var e=t;
return e;
},BottomInputBar.prototype.__filterWordsLimit=function(t){
var e=t;
return e;
},BottomInputBar.prototype.addListener=function(t,e){
return"string"!=typeof t?void console.error("[BottomInputBar] event must be a string"):void(this.state.listener[t]=e);
},BottomInputBar.prototype.show=function(t,e,i){
var n=this;
if(!this.state.show){
if(this.$mask.css("display",""),this.__failToShowChecker=setTimeout(function(){
n.hide(),n.__emit("fail");
},1e3),mmversion.isIOS){
JSAPI.invoke("handleMPPageAction",{
action:"opInputAccessoryView",
show:!1
},function(){});
var o=0;
Device.os.getNumVersion()<13&&(o=this.state.keyboardHeight?(window.innerHeight+this.state.keyboardHeight-this.$inputWrapper.offset().height)/2:window.innerHeight-this.$inputWrapper.offset().height),
this.$inputWrapper.css({
opacity:0,
bottom:o,
transform:"translate3d(0, 10px, 1px)"
}),this.inputEle.focus(),this.__emit("show"),this.state.show=Device.os.getNumVersion()<13?"showing":!0;
}else this.$inputWrapper.css({
opacity:0,
bottom:window.innerHeight
}),this.state.androidShowingKeybroad=!0,this.state.androidOriWinInnerHeight=window.innerHeight,
t?this.__onResize():this.inputEle.focus();
var s=this.inputEle.value.length;
this.inputEle.setSelectionRange(s,s),e&&(this.$el.addClass("comment__push_danmu"),
this.$el.addClass("comment__push_immersive")),i&&this.$el.addClass("comment__push__container__horizontal"),
t&&(this.showEmotionFirst=!0,this.__triggerEmojiPanel());
}
},BottomInputBar.prototype.hide=function(t){
this.state.androidTriggeringEmoji=!1,this.state.show&&(this.state.inChooseEmoji&&(this.state.inChooseEmoji=!1,
this.$el.find(".js_bottom_input_emoji").removeClass("comment__push__keyboard").addClass("comment__push__emoji"),
mmversion.isIOS?JSAPI.invoke("showSmileyPanel",{
hidden:!0
},function(){}):this.$el.find(".js_bottom_input_emoji_panel").css("display","none")),
mmversion.isIOS?JSAPI.invoke("handleMPPageAction",{
action:"opInputAccessoryView",
show:!0
},function(){}):JSAPI.invoke("handleDeviceInfo",{
action:"hideKeyBoard"
},function(){}),this.$inputWrapper.attr("style","opacity: 0; bottom: "+5*window.innerHeight+"px"),
this.$mask.css("display","none"),this.state.show=!1,this.state.androidShowingKeybroad=!1,
this.inputEle.blur(),this.__emit("hide",t),this.$el.removeClass("comment__push_danmu"),
this.$el.removeClass("comment__push_immersive"),this.$el.removeClass("comment__push__container__horizontal"));
},BottomInputBar.prototype.clear=function(){
this.setInputValue("");
},BottomInputBar.prototype.getContent=function(t,e){
return this.inputEle.value.substring(t,e);
},BottomInputBar.prototype.setLimit=function(t){
this.state.limit=t,0!==this.state.limit?this.inputEle.setAttribute("maxlength",this.state.limit):this.inputEle.removeAttribute("maxlength");
},BottomInputBar.prototype.setPlaceholder=function(t){
this.opt.placeholder=t,this.inputEle.setAttribute("placeholder",this.__filterContent(this.opt.placeholder));
},BottomInputBar.prototype.setInputValue=function(t){
this.inputEle.value=t,$(".js_bottom_input_faker").html(t.replace(/\n/g,"<br/>"));
},BottomInputBar.prototype.setContent=function(t){
var e=this.__filterContent(t);
this.setInputValue(e),this.__emit("input",{
data:t,
inputType:"setContent"
});
},BottomInputBar.prototype.insertContent=function(t){
var e=this.getContent(0,this.inputEle.selectionStart),i=this.getContent(this.inputEle.selectionEnd);
if(!(0!==this.state.limit&&t.length+e.length+i.length>this.state.limit)){
var n=this.inputEle.selectionStart+t.length,o=this.__filterContent(e+t+i);
this.setInputValue(o),this.inputEle.setSelectionRange(n,n),this.__emit("input",{
data:t,
inputType:"insertContent"
});
}
},BottomInputBar.prototype.delContent=function(){
var t=this.getContent(0,this.inputEle.selectionStart),e=this.getContent(this.inputEle.selectionEnd),i=void 0,n=void 0,o=void 0;
if(this.inputEle.selectionStart===this.inputEle.selectionEnd){
for(var s=0;s<emojiData.length;s++){
var a=emojiData[s];
if(a.cn&&t.endsWith(a.cn)){
i=t.substring(0,t.length-a.cn.length)+e,n=t.substring(t.length-a.cn.length,t.length),
o=this.inputEle.selectionStart-a.cn.length;
break;
}
if(a.hk&&t.endsWith(a.hk)){
i=t.substring(0,t.length-a.hk.length)+e,n=t.substring(t.length-a.hk.length,t.length),
o=this.inputEle.selectionStart-a.hk.length;
break;
}
if(a.us&&t.endsWith(a.us)){
i=t.substring(0,t.length-a.us.length)+e,n=t.substring(t.length-a.us.length,t.length),
o=this.inputEle.selectionStart-a.us.length;
break;
}
if(a.emoji&&t.endsWith(a.emoji)){
i=t.substring(0,t.length-a.emoji.length)+e,n=t.substring(t.length-a.emoji.length,t.length),
o=this.inputEle.selectionStart-a.emoji.length;
break;
}
}
"string"!=typeof i&&(i=t.substring(0,t.length-1)+e,n=t[t.length-1],o=this.inputEle.selectionStart-1);
}else i=t+e,n=this.getContent(this.inputEle.selectionStart,this.inputEle.selectionEnd),
o=this.inputEle.selectionStart;
i=this.__filterContent(i),this.setInputValue(i),this.inputEle.setSelectionRange(o,o),
this.__emit("input",{
data:n,
inputType:"delContent"
});
},BottomInputBar.prototype.__initEmojiPanel=function(){
for(var t=this,e=16,i=7,n=34,o=[],s={},a=[],r=0;r<panelData.length;r++)for(var h=0;h<emojiData.length;h++)if(emojiData[h].id===panelData[r]){
a[r]=emojiData[h];
break;
}
for(var r=0;i>r;r++)for(var h=0;e>h;h++){
var m=r*e+h;
a[m]&&o.push({
name:a[m].style,
title:a[m].emoji?a[m].emoji:a[m].cn,
bp:"background-position: 0 -"+m*n+"px;",
id:a[m].id
});
}
for(var r=0;r<a.length;r++)s[a[r].style]=a[r].emoji||a[r].cn;
var p=document.createDocumentFragment();
o.forEach(function(t,e){
var i=document.createElement("li"),n=document.createElement("span");
i.className="comment_primary_emotion_item js_emotion_item",i.setAttribute("data-index",e),
n.className="comment_primary_emotion",n.setAttribute("style",t.bp),n.setAttribute("text-name",t.name),
n.setAttribute("role","button"),n.setAttribute("title",t.title),i.appendChild(n),
p.appendChild(i);
}),this.$el.append('<div class="js_bottom_input_emoji_panel comment__emoji__panel" style="display: none;"></div>'),
this.$el.find(".js_bottom_input_emoji_panel").append(p);
var u=void 0;
DomEvent.on(this.$el.find(".js_bottom_input_emoji_panel")[0],"touchstart",function(t){
u=t.changedTouches[0].clientY;
}),DomEvent.on(this.$el.find(".js_bottom_input_emoji_panel")[0],"touchmove",function(e){
var i=e.changedTouches[0].clientY,n=t.$el.find(".js_bottom_input_emoji_panel")[0].scrollTop,o=t.$el.find(".js_bottom_input_emoji_panel")[0].scrollHeight,s=t.$el.find(".js_bottom_input_emoji_panel")[0].clientHeight;
(.5>n&&i>u||.5>o-n-s&&u>i)&&e.preventDefault();
}),DomEvent.on(this.$el.find(".js_bottom_input_emoji_panel")[0],"click",function(e){
if("comment_primary_emotion"===e.target.className){
var i=s[e.target.getAttribute("text-name")];
i&&t.insertContent(i);
}
});
},BottomInputBar;
});define("a/appdialog_confirm.html.js",[],function(){
return'<div class="wx_profile_dialog_primary">\n    <div class="weui-mask"></div>\n    <div class="weui-dialog weui-skin_android">\n        <div class="weui-dialog__hd"><strong class="weui-dialog__title">是否立即下载该应用</strong></div>\n        <div class="weui-dialog__bd">\n            <div class="weui-flex">\n                <div class="wx_profile_info_avatar_wrp">\n                    <span class="wx_profile_info_avatar">\n                        <img src="<#=app_img_url#>" alt="">\n                    </span>\n                </div>\n                <div class="weui-flex__item">\n                    <strong class="wx_profile_info_title"><#=app_name#></strong>\n                </div>\n            </div>\n        </div>\n        <div class="weui-dialog__ft">\n            <a href="javascript:;" class="js_cancel weui-dialog__btn weui-dialog__btn_default">取消</a>\n            <a href="javascript:;" class="js_ok weui-dialog__btn weui-dialog__btn_primary">下载</a>\n        </div>\n    </div>\n</div>\n';
});;define('widget/wx_profile_dialog_primary.css', [], function(require, exports, module) {
	return ".radius_avatar{display:inline-block;background-color:#fff;padding:3px;border-radius:50%;-moz-border-radius:50%;-webkit-border-radius:50%;overflow:hidden;vertical-align:middle}.radius_avatar img{display:block;width:100%;height:100%;border-radius:50%;-moz-border-radius:50%;-webkit-border-radius:50%;background-color:#eee}.wx_profile_dialog_primary .weui-mask{position:fixed;z-index:1000;top:0;right:0;left:0;bottom:0;background:rgba(0,0,0,0.6)}.wx_profile_dialog_primary .weui-dialog{position:fixed;z-index:5000;width:80%;max-width:300px;top:50%;left:50%;-webkit-transform:translate(-50%,-65%);transform:translate(-50%,-65%);background-color:#fff;text-align:center;border-radius:3px;overflow:hidden}.wx_profile_dialog_primary .weui-dialog__hd{position:relative;padding:20px 20px 10px;text-align:left}.wx_profile_dialog_primary .weui-dialog__hd:after{content:\" \";position:absolute;left:20px;right:20px;bottom:0;height:1px;border-bottom:1px solid #d5d5d6;color:#d5d5d6;-webkit-transform-origin:0 100%;transform-origin:0 100%;-webkit-transform:scaleY(0.5);transform:scaleY(0.5)}.wx_profile_dialog_primary .weui-dialog__title{font-weight:400;font-size:17px}.wx_profile_dialog_primary .weui-dialog__bd{padding:16px 20px;min-height:40px;font-size:15px;line-height:1.3;word-wrap:break-word;-webkit-hyphens:auto;-ms-hyphens:auto;hyphens:auto;color:#999}.wx_profile_dialog_primary .weui-dialog__bd:first-child{padding:2.7em 20px 1.7em;color:#353535}.wx_profile_dialog_primary .weui-dialog__ft{position:relative;line-height:44px;font-size:17px;display:-webkit-box;display:-webkit-flex;display:flex}.wx_profile_dialog_primary .weui-dialog__ft:after{content:\" \";position:absolute;left:0;top:0;right:0;height:1px;border-top:1px solid #d5d5d6;color:#d5d5d6;-webkit-transform-origin:0 0;transform-origin:0 0;-webkit-transform:scaleY(0.5);transform:scaleY(0.5)}.wx_profile_dialog_primary .weui-dialog__btn{display:block;-webkit-box-flex:1;-webkit-flex:1;flex:1;color:#3cc51f;text-decoration:none;-webkit-tap-highlight-color:rgba(0,0,0,0);position:relative}.wx_profile_dialog_primary .weui-dialog__btn:active{background-color:#eee}.wx_profile_dialog_primary .weui-dialog__btn:after{content:\" \";position:absolute;left:0;top:0;width:1px;bottom:0;border-left:1px solid #d5d5d6;color:#d5d5d6;-webkit-transform-origin:0 0;transform-origin:0 0;-webkit-transform:scaleX(0.5);transform:scaleX(0.5)}.wx_profile_dialog_primary .weui-dialog__btn:first-child:after{display:none}.wx_profile_dialog_primary .weui-dialog__btn_default{color:#353535}.wx_profile_dialog_primary .weui-dialog__btn_primary{color:#1aad19}.wx_profile_dialog_primary .weui-skin_android .weui-dialog{text-align:left;box-shadow:0 6px 30px 0 rgba(0,0,0,0.1)}.wx_profile_dialog_primary .weui-skin_android .weui-dialog__title{font-size:21px}.wx_profile_dialog_primary .weui-skin_android .weui-dialog__hd{text-align:left;padding:1.3em 1.6em 1.2em}.wx_profile_dialog_primary .weui-skin_android .weui-dialog__hd:after{display:none}.wx_profile_dialog_primary .weui-skin_android .weui-dialog__bd{color:#999;padding:0 1.6em 1.4em;font-size:17px;text-align:left}.wx_profile_dialog_primary .weui-skin_android .weui-dialog__bd:first-child{padding:1.6em 1.6em 2em;color:#353535}.wx_profile_dialog_primary .weui-skin_android .weui-dialog__ft{display:block;text-align:right;line-height:42px;font-size:16px;padding:0 1.6em .7em}.wx_profile_dialog_primary .weui-skin_android .weui-dialog__ft:after{display:none}.wx_profile_dialog_primary .weui-skin_android .weui-dialog__btn{display:inline-block;vertical-align:top;padding:0 .8em}.wx_profile_dialog_primary .weui-skin_android .weui-dialog__btn:after{display:none}.wx_profile_dialog_primary .weui-skin_android .weui-dialog__btn:active{background-color:rgba(0,0,0,0.06)}.wx_profile_dialog_primary .weui-skin_android .weui-dialog__btn:visited{background-color:rgba(0,0,0,0.06)}.wx_profile_dialog_primary .weui-skin_android .weui-dialog__btn:last-child{margin-right:-0.8em}.wx_profile_dialog_primary .weui-skin_android .weui-dialog__btn_default{color:#808080}@media screen and (min-width:1024px){.wx_profile_dialog_primary .weui-dialog{width:35%}}.wx_profile_dialog_primary .weui-flex{display:-webkit-box;display:-webkit-flex;display:flex}.wx_profile_dialog_primary .weui-flex__item{-webkit-box-flex:1;-webkit-flex:1;flex:1}.wx_profile_dialog_primary .weui-flex{-webkit-box-align:center;-webkit-align-items:center;align-items:center}.wx_profile_dialog_primary .weui-flex__item{word-wrap:break-word;-webkit-hyphens:auto;-ms-hyphens:auto;hyphens:auto}.wx_profile_info_avatar_wrp{padding-right:10px}.wx_profile_info_avatar{width:50px;height:50px;padding:0;display:inline-block;background-color:#fff;vertical-align:middle}.wx_profile_info_avatar img{display:block;width:100%;border-radius:10px}.wx_profile_info_title{display:block;overflow:hidden;text-overflow:ellipsis;display:-webkit-box;-webkit-box-orient:vertical;-webkit-line-clamp:2;font-size:16px;font-weight:400;text-align:left}";
});