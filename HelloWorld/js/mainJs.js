/*loading*/
window.onload=function(){
  $("#loading").hide();
}
$(document).ready(function(){
  /*书签及相关信息*/
  $('#toPanorama').click(function(){
    $("html,body").animate({scrollTop:$("#panorama").offset().top},500);
  })
  $('#toCityDscb').click(function(){
    $("html,body").animate({scrollTop:$("#cityDscb").offset().top},500);
  })
  $('#toHistory').click(function(){
    $("html,body").animate({scrollTop:$("#history").offset().top},500);
  })
  $('#toLife').click(function(){
    $("html,body").animate({scrollTop:$("#life").offset().top},500);
  })
  $('#toCulture').click(function(){
    $("html,body").animate({scrollTop:$("#culture").offset().top},500);
  })
  $('#toFood').click(function(){
    $("html,body").animate({scrollTop:$("#food").offset().top},500);
  })
  $('#topImg').click(function(){
    $("html,body").animate({scrollTop:$("#panorama").offset().top},500);
  })
  $('#reloadImg').click(function(){
    location.reload();
  })
  $('#aboutUs').click(function(){
    alert('开发小组成员：蒋棋旋、何晨郡、阿克达\n开始你的旅途吧～');
  })
  $('#contact').click(function(){
    alert('开发者邮箱：jxuan7@foxmail.com');
  })
  /*随机到达城市*/
  $('#travel').click(function(){
    var x=39;
    var y=1;//生成1～39的随机数
    var random=parseInt(Math.random()*(x-y+1)+y);
    $(location).attr('href','./'+random+'.html');
  })
  /*轮播图*/
  var i=0;
  var timer;
  $('.turn .pic img').eq(0).show().siblings().hide();
  start();
  $('b').hover(function(){
    clearInterval(timer);
    i=$(this).index();
    change();
  });
  $('b').mouseleave(function(){
    start();
  });
  function start(){
    timer=setInterval(function(){
      i++;
      if(i==5){
        i=0;//5张图片，当索引为4时清零
      }
      change();
    },3000)//2000ms切换一次图片
  };
  function change(){
    $('.turn .pic img').eq(i).fadeIn(800).siblings().stop().fadeOut(800);//图片显示方式，淡入淡出
    $('b').eq(i).addClass('rudis').siblings().removeClass('rudis');//设置小圆点的背景颜色改变
  }
})