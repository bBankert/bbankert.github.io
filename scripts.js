

function frame() {
        if(pos >= 350){
        y = Math.floor((Math.random()*300)+1);
        elem.style.bottom = y +'px';
        elem.style.left = 0;
        pos = 0
        document.getElementById("animate").innerHTML='y'+y;
    }  else {
        pos++;
        elem.style.left = pos + 'px'; 
    }

}
function openNav(){
    document.getElementById("navBar").style.width="250px";
    document.getElementById("main").style.marginLeft="250px";
}     

function closeBar(){
    document.getElementById("navBar").style.width="0";
    document.getElementById("main").style.marginLeft="0";
}
    
$(document).ready(function(){
    $("a").on('click',function(event){
        if(this.hash !== ""){
            event.preventDefault();
            
            var hash = this.hash;
            
            $('html, body').animate({scrollTop: $(hash).offset().top},800,function(){
                
                window.location.hash = hash;
            });
        }
    });
});
