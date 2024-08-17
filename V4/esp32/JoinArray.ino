String JoinArray(JSONVar arrayData) {
  String joinedString = "";

  for (int i = 0; i < arrayData.length(); i++) {
    joinedString = joinedString + String(arrayData[i]).charAt(0) + " ";
  }

  return joinedString;
}