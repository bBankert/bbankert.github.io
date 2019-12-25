function addActiveClass(id){
    //remove active element
    var activeElement = document.querySelector('.active');
    if(activeElement){
        activeElement.classList.remove('active');
    }
    //set new active element
    var clickedElement = document.getElementById(id);
    clickedElement.classList.add('active');
}
