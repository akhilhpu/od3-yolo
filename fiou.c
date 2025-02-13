#include <stdio.h>
#include <math.h>

// Structure to represent bounding boxes
typedef struct {
  float x1, y1, x2, y2;
} BoundingBox;

// Function to calculate Intersection over Union (IoU)
float calculateIoU(BoundingBox box1, BoundingBox box2) {
  float xA = fmax(box1.x1, box2.x1);
  float yA = fmax(box1.y1, box2.y1);
  float xB = fmin(box1.x2, box2.x2);
  float yB = fmin(box1.y2, box2.y2);

  float interArea = fmax(0, xB - xA + 1) * fmax(0, yB - yA + 1);
  float box1Area = (box1.x2 - box1.x1 + 1) * (box1.y2 - box1.y1 + 1);
  float box2Area = (box2.x2 - box2.x1 + 1) * (box2.y2 - box2.y1 + 1);

  float iou = interArea / (box1Area + box2Area - interArea);
  return iou;
}

// Function to calculate Focal-IoU
float calculateFocalIoU(BoundingBox box1, BoundingBox box2, float gamma) {
  float iou = calculateIoU(box1, box2);
  float focal_iou = pow(iou, gamma) * (1 - calculateIoU(box1, box2)); 
  return focal_iou;
}

int main() {
  // Example usage
  BoundingBox box1 = {10, 10, 20, 20};
  BoundingBox box2 = {15, 15, 25,