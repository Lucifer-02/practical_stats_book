## Chapter 1. Exploratory Data Analysis

### Elements of Structured Data

### Rectangular Data

- [ ] Data Frames and Indexes
- [ ] Nonrectangular Data Structures

### Estimates of Location

- [x] Mean
- [ ] Median and Robust Estimates
- [ ] Example: Location Estimates of Population and Murder Rates

### Estimates of Variability

- [ ] Standard Deviation and Related Estimates
- [ ] Estimates Based on Percentiles
- [ ] Example: Variability Estimates of State Population

### Exploring the Data Distribution

- [ ] Percentiles and Boxplots
- [ ] Frequency Tables and Histograms
- [ ] Density Plots and Estimates

### Exploring Binary and Categorical Data

- [ ] Mode
- [ ] Expected Value
- [ ] Probability

### Correlation

- [ ] Scatterplots

### Exploring Two or More Variables

- [ ] Hexagonal Binning and Contours (Plotting Numeric Versus Numeric Data)
- [ ] Two Categorical Variables
- [ ] Categorical and Numeric Data
- [ ] Visualizing Multiple Variables

## Chapter 2. Data and Sampling Distributions

### Random Sampling and Sample Bias

- [ ] Bias
- [ ] Random Selection
- [ ] Size Versus Quality: When Does Size Matter?
- [ ] Sample Mean Versus Population Mean

### Selection Bias

- [ ] Regression to the Mean

### Sampling Distribution of a Statistic

- [ ] Central Limit Theorem
- [ ] Standard Error

### The Bootstrap

- [ ] Resampling Versus Bootstrapping

### Confidence Intervals

### Normal Distribution

- [ ] Standard Normal and QQ-Plots

### Long-Tailed Distributions

### Student’s t-Distribution

### Binomial Distribution

### Chi-Square Distribution

### F-Distribution

### Poisson and Related Distributions

- [ ] Poisson Distributions
- [ ] Exponential Distribution
- [ ] Estimating the Failure Rate
- [ ] Weibull Distribution

## Chapter 3. Statistical Experiments and Significance Testing

### A/B Testing

- [ ] Why Have a Control Group?
- [ ] Why Just A/B? Why Not C, D,…?

### Hypothesis Tests

- [ ] The Null Hypothesis
- [ ] Alternative Hypothesis
- [ ] One-Way Versus Two-Way Hypothesis Tests

### Resampling

- [ ] Permutation Test
- [ ] Example: Web Stickiness
- [ ] Exhaustive and Bootstrap Permutation Tests
- [ ] Permutation Tests: The Bottom Line for Data Science

### Statistical Significance and p-Values

- [ ] p-Value
- [ ] Alpha
- [ ] Type 1 and Type 2 Errors
- [ ] Data Science and p-Values

### t-Tests

### Multiple Testing

### Degrees of Freedom

### ANOVA

- [ ] F-Statistic
- [ ] Two-Way ANOVA

### Chi-Square Test

- [ ] Chi-Square Test: A Resampling Approach
- [ ] Chi-Square Test: Statistical Theory
- [ ] Fisher’s Exact Test
- [ ] Relevance for Data Science

### Multi-Arm Bandit Algorithm

### Power and Sample Size

- [ ] Sample Size

## Chapter 4. Regression and Prediction

### Simple Linear Regression

- [ ] The Regression Equation
- [ ] Fitted Values and Residuals
- [ ] Least Squares
- [ ] Prediction Versus Explanation (Profiling)

### Multiple Linear Regression

- [ ] Example: King County Housing Data
- [ ] Assessing the Model
- [ ] Cross-Validation
- [ ] Model Selection and Stepwise Regression
- [ ] Weighted Regression

### Prediction Using Regression

- [ ] The Dangers of Extrapolation
- [ ] Confidence and Prediction Intervals

### Factor Variables in Regression

- [ ] Dummy Variables Representation
- [ ] Factor Variables with Many Levels
- [ ] Ordered Factor Variables

### Interpreting the Regression Equation

- [ ] Correlated Predictors
- [ ] Multicollinearity
- [ ] Confounding Variables
- [ ] Interactions and Main Effects

### Regression Diagnostics

- [ ] Outliers
- [ ] Influential Values
- [ ] Heteroskedasticity, Non-Normality, and Correlated Errors
- [ ] Partial Residual Plots and Nonlinearity

### Polynomial and Spline Regression

- [ ] Polynomial
- [ ] Splines
- [ ] Generalized Additive Models

## Chapter 5. Classification

### Naive Bayes

- [ ] Why Exact Bayesian Classification Is Impractical
- [ ] The Naive Solution
- [ ] Numeric Predictor Variables

### Discriminant Analysis

- [ ] Covariance Matrix
- [ ] Fisher’s Linear Discriminant
- [ ] A Simple Example

### Logistic Regression

- [ ] Logistic Response Function and Logit
- [ ] Logistic Regression and the GLM
- [ ] Generalized Linear Models
- [ ] Predicted Values from Logistic Regression
- [ ] Interpreting the Coefficients and Odds Ratios
- [ ] Linear and Logistic Regression: Similarities and Differences
- [ ] Assessing the Model

### Evaluating Classification Models

- [ ] Confusion Matrix
- [ ] The Rare Class Problem
- [ ] Precision, Recall, and Specificity
- [ ] ROC Curve
- [ ] AUC
- [ ] Lift

### Strategies for Imbalanced Data

- [ ] Undersampling
- [ ] Oversampling and Up/Down Weighting
- [ ] Data Generation
- [ ] Cost-Based Classification
- [ ] Exploring the Predictions

## Chapter 6. Statistical Machine Learning

### K-Nearest Neighbors

- [ ] A Small Example: Predicting Loan Default
- [ ] Distance Metrics
- [ ] One Hot Encoder
- [ ] Standardization (Normalization, z-Scores)
- [ ] Choosing K
- [ ] KNN as a Feature Engine

### Tree Models

- [ ] A Simple Example
- [ ] The Recursive Partitioning Algorithm
- [ ] Measuring Homogeneity or Impurity
- [ ] Stopping the Tree from Growing
- [ ] Predicting a Continuous Value
- [ ] How Trees Are Used

### Bagging and the Random Forest

- [ ] Bagging
- [ ] Random Forest
- [ ] Variable Importance
- [ ] Hyperparameters

### Boosting

- [ ] The Boosting Algorithm
- [ ] XGBoost
- [ ] Regularization: Avoiding Overfitting
- [ ] Hyperparameters and Cross-Validation

## Chapter 7. Unsupervised Learning

### Principal Components Analysis

- [ ] A Simple Example
- [ ] Computing the Principal Components
- [ ] Interpreting Principal Components
- [ ] Correspondence Analysis

### K-Means Clustering

- [ ] A Simple Example
- [ ] K-Means Algorithm
- [ ] Interpreting the Clusters
- [ ] Selecting the Number of Clusters

### Hierarchical Clustering

- [ ] A Simple Example
- [ ] The Dendrogram
- [ ] The Agglomerative Algorithm
- [ ] Measures of Dissimilarity

### Model-Based Clustering

- [ ] Multivariate Normal Distribution
- [ ] Mixtures of Normals
- [ ] Selecting the Number of Clusters

### Scaling and Categorical Variables

- [ ] Scaling the Variables
- [ ] Dominant Variables
- [ ] Categorical Data and Gower’s Distance
- [ ] Problems with Clustering Mixed Data
