//class and id have same names. id - #getstart  class - .getstart 
$(document).ready(function(){
    ids = ["#getstart","#reqfiles","#runapp","#errhand","#newgen","#imgsamp","#repsamp"];
    ids.forEach(element => {$("." + element.slice(1)).hide();});
    $(".getstart").show();
        
    ids.forEach(element => {$(element).click(function(){
      $("." + element.slice(1)).show();
    clicked_element = element;
      ids.forEach(element => {if(element!=clicked_element){$("." + element.slice(1)).hide();}});
    
    });
  
    
  });

  $('#field').click(function() {
    this.classList.toggle("active");
    var content = this.nextElementSibling;
    if (content.style.display === "block") {
      content.style.display = "none";
    } else {
      //content.innerHTML = document.getElementById('field-description').innerHTML;
      content.innerHTML = $("#field-description").html();
      content.style.display = "block";
    }
  });

  $('#materials').click(function() {
    this.classList.toggle("active");
    var content = this.nextElementSibling;
    if (content.style.display === "block") {
      content.style.display = "none";
    } else {
      //content.innerHTML = document.getElementById('field-description').innerHTML;
      content.innerHTML = $("#material-description").html();
      content.style.display = "block";
    }

  });

 });




//$("." + element.slice(1)).hide();});