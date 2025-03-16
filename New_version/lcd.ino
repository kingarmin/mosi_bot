void face_talk() {
  for (int i = 0; i < 8; i++) {
    lc.setRow(1, i, open_eye[i]);
    lc.setRow(7, 7-i, open_eye[i]);
    lc.setRow(5, i, open_eye[i]);
    lc.setRow(3, 7 - i, open_eye[i]);
  }
  for (int i = 0; i < 8; i++) {
    lc.setRow(4, i, open_month[i]);
    lc.setRow(2, 7 - i, open_month[i]);
  }
  delay(100);
  for (int i = 0; i < 8; i++) {
    lc.setRow(1, i, close_eye[i]);
    lc.setRow(7, 7 - i, close_eye[i]);
    lc.setRow(5, i, close_eye[i]);
    lc.setRow(3, 7 - i, close_eye[i]);
  }
  delay(1000);
  for (int i = 0; i < 8; i++) {
    lc.setRow(1, i, open_eye[i]);
    lc.setRow(7, 7 - i, open_eye[i]);
    lc.setRow(5, i, open_eye[i]);
    lc.setRow(3, 7 - i, open_eye[i]);
  }
  for (int i = 0; i < 8; i++) {
    lc.setRow(4, i, close_mounth[i]);
    lc.setRow(2, 7 - i, close_mounth[i]);
  }
  delay(1000);
  for (int i = 0; i < 8; i++) {
    lc.setRow(4, i, open_month[i]);
    lc.setRow(2, 7 - i, open_month[i]);
  }
}
void free_face() {
  delay(500);
  for (int i = 0; i < 8; i++) {
    lc.setRow(4, i, close_mounth[i]);
    lc.setRow(2, 7 - i, close_mounth[i]);
  }
  for (int i = 0; i < 8; i++) {
    lc.setRow(1, i, close_eye[i]);
    lc.setRow(7, 7 - i, close_eye[i]);
    lc.setRow(5, i, close_eye[i]);
    lc.setRow(3, 7 - i, close_eye[i]);
  }
  delay(1000);
  for (int i = 0; i < 8; i++) {
    lc.setRow(1, i, open_eye[i]);
    lc.setRow(7, 7 - i, open_eye[i]);
    lc.setRow(5, i, open_eye[i]);
    lc.setRow(3, 7 - i, open_eye[i]);
  }
}