//render the queried callee and whoever calls it
function queryGraph() {
	var callee = document.forms["codeQuery"].elements["callee"].value;
	renderFunctionAndAncestors(callee);
  
}

function renderFunctionAndAncestors(func) {
  var renderString = "digraph CallGraph {\n"
	if (func) {
		renderParents(func);
	}
  
  renderString += "}\n";
  
  svg = Viz(renderString, "svg");
  document.getElementById("callgraph").innerHTML = svg;

	function renderParents(node) {
    for (var i = 0; i < graphEdges.length; i++) {
      if (graphEdges[i].functionName.toLowerCase() == node.toLowerCase()) {
          renderString += '"' + graphEdges[i].called_by + "\" -> \"" + graphEdges[i].functionName + "\";\n";
          renderParents(graphEdges[i].called_by);
      }
    }
	}
}
